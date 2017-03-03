#include <cstring>
#include "EzClient.h"

using namespace std;
using namespace EzChat;

EzClient::EzClient() {
    port_ = 1501;
    kill_ = false;
}
EzClient::EzClient(ClientMessageHandler h, int port) 
: mHandler_(h) {
    port_ = port;
    kill_ = false;

}

int EzClient::start() {
    mHandler_.initializeConnection();

    if (mHandler_.isConnected()) {
        eHandler_.logError("Error connecting client socket..");
	return 1;
    }
    cout << "-->Client socket established.. " << endl;

    mHandler_.createSocket(port_);

    cout << "-->Client socket created.." << endl;
    int res = mHandler_.handleConnect();
    if (res == 0) {
        cout << "-->Connection to the server port number " + to_string(port_)+ " established.." << endl;
    } else {
        eHandler_.logError("Error connecting to server..");
    }
    cout << "-->Server connection established .." << endl;

    mHandler_.confirmConnection();

    while (1) {
        cout << "Client: ";
        // grab input
        string msg;
        getline(cin, msg);

        if (msg == "kill")
            break;

        // send msg to server
        mHandler_.sendMessage(msg);

        // receive msg received
        string s = mHandler_.handleReceive();
        if (s.at(0) == '-') {
            cout << s.substr(1) << endl;
     }
    }
    cout << "Closing..." << endl;

    mHandler_.handleClose();

    return 0;
}

