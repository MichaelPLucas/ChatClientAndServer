#include "ServerMessageHandler.h"

using namespace std;
using namespace EzChat;

ServerMessageHandler::ServerMessageHandler(string ip, int msgSize)
    : ip_(ip), msgSize_(msgSize) {}

void ServerMessageHandler::sendMessage(string message) const noexcept {
    handleSend(message.c_str(), msgSize_);
}

void ServerMessageHandler::initializeConnection() noexcept {
    cout << "-->Initializing Connection.." << endl;
    fd_ = socket(AF_INET, SOCK_STREAM, 0);
}

bool ServerMessageHandler::isConnected() const noexcept {
    return fd_ < 0;
}

void ServerMessageHandler::createSocket(int port) {
    server_address_.sin_family = AF_INET;
    // convert port number to number-byte order
    server_address_.sin_port = htons(port);
    server_address_.sin_addr.s_addr = htons(INADDR_ANY);
}

int ServerMessageHandler::handleConnect() noexcept {
    return bind(fd_, (struct sockaddr*)&server_address_, sizeof(server_address_));
}

bool ServerMessageHandler::couldNotBind() {
    socklen_t size = sizeof(server_address_);
    bound_ = accept(fd_, (struct sockaddr*)&server_address_, &size);
    cout << "-->Connection accepted.." << endl;
    return bound_ < 0;
}

int ServerMessageHandler::handleListen() {
    return listen(fd_, 1);
}

bool ServerMessageHandler::confirmConnection() noexcept {
    char temp[msgSize_];
    memset(temp, 0, msgSize_);
    strcpy(temp, "-->Server joined the room..\n");
    send(bound_, temp, msgSize_, 0);
    memset(temp, 0, msgSize_);
    cout << "-->Connected to client " << endl;
    cout << "-->Input kill to end chat" << endl;
    recv(bound_, temp, msgSize_, 0);
    cout <<"Client: ";
    cout << temp << endl;
    log_.push_back(string(temp));
    return true;
}

void ServerMessageHandler::handleSend(const char* buffer, int size) const noexcept {
    send(bound_, buffer, size, 0);
}

string  ServerMessageHandler::handleReceive() noexcept {
    char temp[msgSize_];
    memset(temp, 0, msgSize_);
    recv(bound_, temp, msgSize_, 0);
    cout << "Client: ";
    string msg = string(temp);
    if (msg == "-log") {
        string log = "-";
        for (auto c : log_) {
            log += c + "\n";
        }
        sendMessage(log);
    } else {
        log_.push_back(msg);
    }
    cout << temp << endl;
    return msg;
}

void ServerMessageHandler::handleClose() noexcept {
    cout << "Killing server at IP: " << inet_ntoa(server_address_.sin_addr);
    // close file descriptor
    close(bound_);
}
