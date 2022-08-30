#include "Settings.hpp"

Settings::Settings(/* args */)
{
    ip = "0.0.0.0";
    http_port = 8080;
    https_port = 8443;
    redis_url = "redis://127.0.0.1:6379/0";
}


