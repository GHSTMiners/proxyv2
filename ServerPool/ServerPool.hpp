
// Libuv
#include <uv.h>

// uWebsockets
#include <App.h>

// SPDlog
#include <spdlog/spdlog.h>

// Hiredis
#include <async.h>
#include <hiredis.h>
#include <adapters/libuv.h>

// Internal headers
#include "ServerHandle.hpp"
#include "Settings/Settings.hpp"

class ServerPool
{
public:
    ServerPool(const Settings &settings);
    ~ServerPool();

protected:
    static void connectCallback(const redisAsyncContext *c, int status);
    static void disconnectCallback(const redisAsyncContext *c, int status);
    static void updateCallback(redisAsyncContext *c, void *r, void *privdata);
    static void subscriptionCallback(redisAsyncContext *c, void *r, void *privdata);

private:
    const Settings &settings;
    static redisReader *reader;
    static redisAsyncContext *redisContext;
    static std::map<std::string, pServerHandle> nodes;
};

