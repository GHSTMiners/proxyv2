#include <stdio.h>
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>

int main(int argc, char const *argv[])
{
    printf("Hello world\n");

    // Start server
    websocketpp::server<websocketpp::config::asio> server;
    server.init_asio();
    server.listen(443);
    server.start_accept();
    server.run();

    return 0;
}
