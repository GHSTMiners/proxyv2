#include "Bootstrapper.hpp"

void Bootstrapper::bootstrap(int argc, char const *argv[]) {
    spdlog::debug("Bootstrapping Colyseus proxy");
    process_environment();
    parse_arguments(argc, argv);
    print_info();
}

void Bootstrapper::process_environment() {
    spdlog::debug("Processing environment variables");
    try {
        if(std::getenv("IP")) settings.ip = std::string(std::getenv("IP"));
        if(std::getenv("HTTP_PORT")) settings.http_port = std::stoi(std::getenv("HTTP_PORT"));
        if(std::getenv("HTTPS_PORT")) settings.https_port = std::stoi(std::getenv("HTTPS_PORT"));
        if(std::getenv("SSL_CERT")) settings.ssl_cert = std::string(std::getenv("SSL_CERT"));
        if(std::getenv("SSL_KEY")) settings.ssl_cert = std::string(std::getenv("SSL_KEY"));
        if(std::getenv("REDIS_URL")) settings.ssl_cert = std::string(std::getenv("REDIS_URL"));     
    } catch (const std::invalid_argument& err) {
        spdlog::get("console")->critical("Environment variable was malformed!");
    }
}

void Bootstrapper::parse_arguments(int argc, char const *argv[]) {
    //Instante parser
    argparse::ArgumentParser program("Colyseus Proxy", "1.0");
    //Add arguments
    program.add_argument("-i", "--ip").help("IP to bind to (default 0.0.0.0)");
    program.add_argument("-p", "--http-port").help("HTTP listen port");
    program.add_argument("-s", "--https-port").help("HTTPS listen port");
    program.add_argument("-c", "--ssl-cert").help("HTTPS SSL Certificate");
    program.add_argument("-k", "--ssl-key").help("HTTPS SSL Key");
    program.add_argument("-r", "--redis-url").help("URL to connect to redis database");
    program.add_argument("-v", "--verbose").help("Verbose logging").default_value(false).implicit_value(true).action([&](const auto &) {
        spdlog::set_level(spdlog::level::debug);
    });
    // Run parser
    try {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }
}

void Bootstrapper::print_info() {
    spdlog::info("Will attempt to listen on {}:{} (HTTP)", settings.ip, settings.http_port);
    spdlog::info("Will attempt to listen on {}:{} (HTTPS)", settings.ip, settings.https_port);
}
