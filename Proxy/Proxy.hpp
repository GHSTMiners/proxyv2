//Standard library
#include <stdint.h>
#include <functional>

//IXWebsocket
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXWebSocketServer.h>

//SPDlog
#include <spdlog/spdlog.h>

class Proxy
{
public:
    Proxy(uint16_t port, std::string host = "0.0.0.0");
    ~Proxy();

    void handleIncommingConnection(std::weak_ptr<ix::WebSocket> webSocket, std::shared_ptr<ix::ConnectionState> connectionState);
    
private:
    ix::WebSocketServer webSocketServer;
};


