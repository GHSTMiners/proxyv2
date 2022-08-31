#include "ServerPool.hpp" 

redisReader* ServerPool::reader = nullptr;
redisAsyncContext* ServerPool::redisContext = nullptr;
std::map<std::string, pServerHandle> ServerPool::nodes = std::map<std::string, pServerHandle>();

ServerPool::ServerPool(const Settings &settings) : settings(settings) {
    // Connect to redis
    reader = redisReaderCreate();
    redisContext = redisAsyncConnect("127.0.0.1", 6379);
    if(redisContext->err) {
        spdlog::error("Failed to connect to redis, reason: {}", redisContext->errstr);
    } else {

        // Connect redis to main event loop
        uv_loop_t* loop = uv_default_loop();
        redisLibuvAttach(redisContext,loop);

        // Configure callbacks
        redisAsyncSetConnectCallback(redisContext, connectCallback);
        redisAsyncSetDisconnectCallback(redisContext, disconnectCallback);
        redisAsyncSetTimeout(redisContext, (struct timeval){ .tv_sec = 2, .tv_usec = 0});
        redisAsyncCommand(redisContext, updateCallback, this, "smembers colyseus:nodes", 1.5);
        redisAsyncCommand(redisContext, subscriptionCallback, this, "SUBSCRIBE colyseus:nodes:discovery", 1.5);
    }
}

void ServerPool::updateCallback(redisAsyncContext *c, void *r, void *privdata) {
    redisReply *reply = static_cast<redisReply*>(r);
    if(reply->type == REDIS_REPLY_ARRAY) {
        for (size_t currentElement = 0; currentElement < reply->elements; currentElement++) {
            auto serverHandle = ServerHandle::fromRedisString(reply->element[currentElement]->str);
            if(serverHandle) {
                nodes.insert_or_assign(serverHandle->processId, serverHandle);
            } else {
                spdlog::warn("Recieved malformed node info from Redis: {}", reply->element[currentElement]->str);
            }
        }   
    }
    spdlog::info("Retrieved info for {} nodes from Redis", nodes.size());
}

void ServerPool::subscriptionCallback(redisAsyncContext *c, void *r, void *privdata) {
    redisReply *reply = static_cast<redisReply*>(r);
    if(reply->type == REDIS_REPLY_ARRAY && reply->elements == 3 && reply->element[2]->str != nullptr) {
        std::string redisString(reply->element[2]->str);
        redisString.erase(remove( redisString.begin(), redisString.end(), '\"' ),redisString.end());

        // Check if message is valid
        std::regex regexp("(.*?),(.*?)\\w/(.*?):+[1-9]+"); 
        if(std::regex_match(redisString, regexp)) {
            // Split spring and check if is add or remove
            std::string delimiter = ",";
            std::string operation = redisString.substr(0, redisString.find(delimiter));
            std::string data = redisString.substr(redisString.find(delimiter)+1, redisString.length());
            // Process data and convert to server handle
            auto serverHandle = ServerHandle::fromRedisString(data);
            if(serverHandle) {
                if(operation == "add") {
                    if(nodes.count(serverHandle->processId) == 0) {
                        nodes.insert_or_assign(serverHandle->processId, serverHandle);
                        spdlog::info("Server with processId {} was added to the server pool", serverHandle->processId);
                    }
                } else if(operation == "remove") {
                    if(nodes.count(serverHandle->processId) > 0) {
                        nodes.erase(serverHandle->processId);
                        spdlog::info("Server with processId {} was removed from the server pool", serverHandle->processId);
                    }
                }
            } else {
                spdlog::warn("Recieved malformed node info from Redis: {}", data);
            }
        }
    }
}

void ServerPool::connectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        spdlog::error("There was an issue while connecting to redis: {}", c->errstr);
        std::exit(-1);
        return;
    }
    spdlog::info("Succesfully connected to redis");
}

void ServerPool::disconnectCallback(const redisAsyncContext *c, int status) {
        if (status != REDIS_OK) {
        spdlog::error("There was an issue while disconnecting from redis: {}", c->errstr);
        return;
    }
    spdlog::info("Succesfully disconnected from redis");
}


ServerPool::~ServerPool() {
    
}