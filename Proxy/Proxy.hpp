// Standard library
#include <stdint.h>
#include <functional>

// uWebSockets
#include <App.h>

// SPDlog
#include <spdlog/spdlog.h>

// Boost
#include <boost/filesystem.hpp>

// Internal headers
#include "Settings/Settings.hpp"
#include "ServerPool/ServerPool.hpp"

class Proxy
{
public:
    Proxy(const Settings &settings);
    ~Proxy();

protected:
    void start_http();
    void start_https();

    
private:
    uWS::App server;
    uWS::SSLApp sslServer;
    const Settings &settings;
    ServerPool serverPool;
};


