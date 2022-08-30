#include "ServerPool.hpp" 

ServerPool::ServerPool(const Settings &settings) : settings(settings) {
    // Connect to redis
    redisContext = redisAsyncConnect("127.0.0.1", 6379);
    if(redisContext->err) {
        spdlog::error("Failed to connect to redis");
    }

    // Connect redis to main event loop
    uv_loop_t* loop = uv_default_loop();
    redisLibuvAttach(redisContext,loop);

    // Configure callbacks
    redisAsyncSetConnectCallback(redisContext, connectCallback);
    redisAsyncSetDisconnectCallback(redisContext, disconnectCallback);

    redisAsyncCommand(redisContext, getCallback, NULL, "DEBUG SLEEP %f", 1.5);


}

void ServerPool::getCallback(redisAsyncContext *c, void *r, void *privdata) {

}


void ServerPool::connectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        spdlog::error("There was an issue while connecting to redis: {}", c->errstr);
        return;
    }
    spdlog::debug("Succesfully connected to redis");
}

void ServerPool::disconnectCallback(const redisAsyncContext *c, int status) {
        if (status != REDIS_OK) {
        spdlog::error("There was an issue while disconnecting from redis: {}", c->errstr);
        return;
    }
    spdlog::debug("Succesfully disconnected from redis");
}


ServerPool::~ServerPool() {
    
}