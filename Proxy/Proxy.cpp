#include "Proxy.hpp"

Proxy::Proxy(uint16_t port, std::string host) : webSocketServer(port, host)
{
    webSocketServer.setOnConnectionCallback(std::bind(&Proxy::handleIncommingConnection, this, std::placeholders::_1, std::placeholders::_2));
}

void Proxy::handleIncommingConnection(std::weak_ptr<ix::WebSocket> webSocket, std::shared_ptr<ix::ConnectionState> connectionState) {
    // Log incomming connection
    spdlog::info("incomming connection from {}", connectionState->getRemoteIp());
    // Forward connections
    auto socket = webSocket.lock();
    socket->setOnMessageCallback([webSocket, connectionState](const ix::WebSocketMessagePtr& message) {
        if(message->type == ix::WebSocketMessageType::Open) {

        }
    });
}


Proxy::~Proxy()
{
}