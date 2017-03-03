#include "EzServer.h"

using namespace EzChat;

int main() {
    ServerMessageHandler h("127.0.0.1", 1024);
    EzServer server(h, 1501);
    server.start();
}
