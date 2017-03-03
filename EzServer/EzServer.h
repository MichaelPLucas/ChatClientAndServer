#ifndef EZ_SERVER_H
#define EZ_SERVER_H
#include <iostream>
#include <string>
#include <vector>
#include "ErrorHandler.h"
#include "ServerMessageHandler.h"

/**
 * @namespace EzChat contains a simple networked chat client
 * @version 1.0
 */
namespace EzChat {
    /** Represents a chat client server */
    class EzServer {
        public:
            /**
             * Initializes a server with default port
             */
            EzServer();
            /**
             * Initializes a server with the given port
             * @param h is the message handler for this server
             * @param port is the port number of this server
             */
            EzServer(ServerMessageHandler h, int port);
            /**
             * Executes this server to start accepting messages
             * @throw domain_error if the connection could not be establisted.
             */
            int start();

        private:
            /** the port of this server */
            int port_;
            /** max message size */
            const static int msgSize_ = 1024;
            /** kill server? */
            bool kill_;
            /** number of clients */
            int numClients_ = 1;

	        /** The ErrorHandler for the server */
	        EzChat::ErrorHandler eHandler_;
	        /** The MessageHandler for the server */
	        EzChat::ServerMessageHandler mHandler_;
            /**
             * initializes a connection between a client and server
             * @return 0 for success, non-zero otherwise
             */
            int init_connection();

    };
}
#endif
