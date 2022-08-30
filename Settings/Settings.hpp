#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <stdint.h>

class Settings
{
public:
    Settings();
    std::string ip;
    uint16_t http_port;
    uint16_t https_port;
    std::string ssl_cert;
    std::string ssl_key;
    std::string redis_url;
};

#endif