#include "ClientMessageHandler.h"
#include <sstream>
using namespace std;
using namespace EzChat;

ClientMessageHandler::ClientMessageHandler(string ip, int msgSize)
    : ip_(ip), msgSize_(msgSize) {

}

void ClientMessageHandler::sendMessage(std::string message) const noexcept {
    handleSend(message.c_str(), message.length());
}

void ClientMessageHandler::initializeConnection() noexcept {
    cout << "-->Initializing Connection.." << endl;
    fd_ = socket(AF_INET, SOCK_STREAM, 0);
}

bool ClientMessageHandler::isConnected() const noexcept {
    return fd_ < 0;
}

void ClientMessageHandler::createSocket(int port) {
    server_address_.sin_family = AF_INET;
    server_address_.sin_port = htons(port);
    // convert ip to binary, add to server address
    inet_pton(AF_INET, ip_.c_str(), &server_address_.sin_addr);
}

int ClientMessageHandler::handleConnect() noexcept {
    return connect(fd_, (const struct sockaddr*)&server_address_, sizeof(server_address_));
}

bool ClientMessageHandler::confirmConnection() noexcept {
    cout << "-->Waiting for server to confirm connection.." << endl;
    char temp[msgSize_];
    recv(fd_, temp, msgSize_, 0);
    cout << "-->Connection confirmed.." << endl;
    cout <<"-->Type kill to end connection" << endl;
    return 0;
}

void ClientMessageHandler::handleSend(const char* buffer, int size) const noexcept {
    send(fd_, buffer, size, 0);
}

string ClientMessageHandler::handleReceive() noexcept {
    char temp[msgSize_];
    recv(fd_, temp, msgSize_, 0);
    stringstream buf;
    buf << temp << " " << endl;
    return buf.str();
}

void ClientMessageHandler::handleClose() noexcept {
    close(fd_);
}
