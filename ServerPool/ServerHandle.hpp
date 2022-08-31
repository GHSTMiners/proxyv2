#ifndef SERVERHANDLE_H
#define SERVERHANDLE_H

// Standard library
#include <regex>
#include <string>
#include <memory>

// SPDlog
#include <spdlog/spdlog.h>

class ServerHandle
{
public:
    ServerHandle(const std::string &hostname, const uint16_t port, const std::string &processId);

    static std::shared_ptr<ServerHandle> fromRedisString(const std::string redisString);

    const uint16_t port;
    const std::string hostname;
    const std::string processId;
};
typedef std::shared_ptr<ServerHandle> pServerHandle;

#endif