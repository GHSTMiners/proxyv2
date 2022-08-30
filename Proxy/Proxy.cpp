#include "Proxy.hpp"

Proxy::Proxy(const Settings &settings)
{




	uWS::run();
}

void Proxy::start_http() {
    server.listen(settings.ip, settings.http_port, [settings](auto *listen_socket) {
		if (listen_socket) {
			spdlog::info("HTTP server listening on: {}:{}", settings.ip, settings.http_port);
	    } else {
			spdlog::error("HTTP server could not bind to {}:{}", settings.ip, settings.http_port);
		}
	});
}

void Proxy::start_https() {
	if
    sslServer.listen(settings.ip, settings.https_port, [settings](auto *listen_socket) {
	    if (listen_socket) {
			spdlog::info("HTTPS server listening on: {}:{}", settings.ip, settings.https_port);
	    } else {
			spdlog::error("HTTPS server could not bind to {}:{}", settings.ip, settings.https_port);
		}
	});
}




Proxy::~Proxy()
{
}