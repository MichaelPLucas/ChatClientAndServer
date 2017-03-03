#include "EzServer.h"
#include <cstring>

using namespace std;
using namespace EzChat;

EzServer::EzServer() {
    port_ = 1501;
    kill_ = false;
}
EzServer::EzServer(ServerMessageHandler h, int port) 
   :  mHandler_(h) {
    port_ = port;
    kill_ = false;
}

int EzServer::start() {
    mHandler_.initializeConnection();

    if (mHandler_.isConnected()) {
        eHandler_.logError("Error establishing server connection");
        return -1;
    }
    cout << "-->Successfully established server socket.." << endl;
    
    mHandler_.createSocket(port_);
    // bind socket to an address
    int res = mHandler_.handleConnect();
    if (res < 0) {
        eHandler_.logError("Error binding connection, socket is already bound..");
        return -1;
    }

    cout <<"-->Waiting for clients. . . ." << endl;
    res = mHandler_.handleListen();
    if (res == 0) 
        cout << "-->Connection received .." << endl;
    else
        cout << to_string(res) << endl;
    // blocks this process until a client connects
    if (mHandler_.couldNotBind()) {
        eHandler_.logError("Error accepting connection..");
        return -1;
    }

    mHandler_.confirmConnection();



    while (!kill_) {
        // send msg back
        mHandler_.sendMessage("foo");

        // receive a msg
        string msg = mHandler_.handleReceive();
        kill_ = msg == "kill";
    }

    // connection has ended
    mHandler_.handleClose();
   // close(client_);
    return 0;
}
