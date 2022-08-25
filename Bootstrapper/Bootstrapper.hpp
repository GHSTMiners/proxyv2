#include <cstdlib>
#include <argparse/argparse.hpp>
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h" // support for user defined types
#include "../Settings/Settings.hpp"

class Bootstrapper
{
public:
    void bootstrap(int argc, char const *argv[]);
    void process_environment();
    void parse_arguments(int argc, char const *argv[]);
    void print_info();
private:
    Settings settings;
};
