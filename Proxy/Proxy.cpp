#include "Proxy.hpp"

Proxy::Proxy(const Settings &settings) : settings(settings)
{	
	start_http();
	start_https();
}

void Proxy::start_http() {
    server.listen(settings.ip, settings.http_port, [&](auto *listen_socket) {
		if (listen_socket) {
			spdlog::info("HTTP server listening on: {}:{}", settings.ip, settings.http_port);
	    } else {
			spdlog::error("HTTP server could not bind to {}:{}", settings.ip, settings.http_port);
		}
	});
}

void Proxy::start_https() {
	if (settings.ssl_cert.empty() || settings.ssl_key.empty()) {
		spdlog::debug("Certificate or private key path where empty, not starting HTTPS Server");
		return;
	}
	if (!boost::filesystem::exists(settings.ssl_cert)) {
		spdlog::error("Could not find certificate file for HTTPS Server at: {}", settings.ssl_cert);
		return;
	}
	if (!boost::filesystem::exists(settings.ssl_key)) {
		spdlog::error("Could not find certificate private key file for HTTPS Server at: {}", settings.ssl_key);
		return;
	}
    sslServer.listen(settings.ip, settings.https_port, [&](auto *listen_socket) {
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