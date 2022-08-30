// Standard libary[]
#include <cstdlib>

// Argparse
#include <argparse/argparse.hpp>

// SPDLOG
#include <spdlog/spdlog.h>

// Internal headers
#include "../Proxy/Proxy.hpp"
#include "../Settings/Settings.hpp"

class Bootstrapper
{
public:
    void bootstrap(int argc, char const *argv[]);
    void process_environment();
    void parse_arguments(int argc, char const *argv[]);
    void print_info();
    void start_server();
private:
    Settings settings;
};
