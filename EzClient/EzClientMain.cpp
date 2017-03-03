#include "EzClient.h"
using namespace EzChat;
int main() {
    ClientMessageHandler h("127.0.0.1", 1024);
    EzClient client(h, 1501);
    client.start();

}
