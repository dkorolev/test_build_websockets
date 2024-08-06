#include "pls.h"

PLS_ADD("wsServer", "https://github.com/current-deps/wsServer.git");
PLS_DEP("ws");

// NOTE(dkorolev): If forked under the repo called `ws`, just `PLS_ADD_CURRENT_DEP("ws")` will do the job.

#include "websockets.h"

int main() {
  auto server = WebsocketServer(
      [](WebsocketClient &client, std::vector<uint8_t> data, int type) {
        // add end of string
        data.push_back('\0');
        std::cout << "WebSocket Message: " << std::string((char *)(data.data())) << std::endl;
        std::string answer = "Hello from server!";
        std::vector<uint8_t> to_send(answer.begin(), answer.end());
        client.SendText(to_send);
      },
      [](WebsocketClient &client) {
        std::cout << "Client " << client.Address() << ":" << client.Port() << " connected" << std::endl;
      },
      [](WebsocketClient &client) {
        std::cout << "Client " << client.Address() << ":" << client.Port() << " disconnected" << std::endl;
      },
      8080);
  std::cout << "Started WebSocket server on port 8080." << std::endl;
  server.start();
  return 0;
}
