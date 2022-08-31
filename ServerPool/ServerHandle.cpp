#include "ServerHandle.hpp"

ServerHandle::ServerHandle(const std::string &hostname, const uint16_t port, const std::string &processId) :
    hostname(hostname), port(port), processId(processId)
{

}

std::shared_ptr<ServerHandle> ServerHandle::fromRedisString(const std::string redisString) {
    // Check if string matches regex
    std::regex regexp("(.*?)\\w/(.*?):+[1-9]+"); 
    if(!std::regex_match(redisString, regexp)) {
        return nullptr;
    }
    // Split process ID and URI
    std::string delimiter = "/";
    std::string processId = redisString.substr(0, redisString.find(delimiter));
    std::string uri = redisString.substr(redisString.find(delimiter)+1, redisString.length());
    //Split URI into hostname and port
    delimiter = ":";
    std::string hostname = uri.substr(0, uri.find(delimiter));
    uint16_t port = stoi(uri.substr(uri.find(delimiter)+1, uri.length()));
    return std::make_shared<ServerHandle>(hostname, port, processId); 
}

