
// Libuv
#include <uv.h>

// uWebsockets
#include <App.h>

// SPDlog
#include <spdlog/spdlog.h>

// Hiredis
#include <hiredis/async.h>
#include <hiredis/hiredis.h>
#include <hiredis/adapters/libuv.h>

// Internal headers
#include "Settings/Settings.hpp"

class ServerPool
{
public:
    ServerPool(const Settings &settings);
    ~ServerPool();

protected:
    static void getCallback(redisAsyncContext *c, void *r, void *privdata);
    static void connectCallback(const redisAsyncContext *c, int status);
    static void disconnectCallback(const redisAsyncContext *c, int status);

private:
    const Settings &settings;
    redisAsyncContext *redisContext;
};

