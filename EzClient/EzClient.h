#ifndef EZ_CLIENT_H
#define EZ_CLIENT_H
#include <iostream>
#include <string>
#include "ErrorHandler.h"
#include "ClientMessageHandler.h"

namespace EzChat {
    /** represents a simple client */
    class EzClient {
        public:

            /** 
             * initializes a client with default port 
             */
            EzClient();

            /** 
             * initializes a client with the given port
             * @param port is the port of this client
             * @param h is the message handler for this client
             */
            EzClient(ClientMessageHandler h, int port);

            /**
             * starts the client
             * @throw domain_error if the connection fails
             */
            int start();

        private:
            /** port number */
            int port_;
            /** kill client? */
            bool kill_;
            /** msg size */
            const static int msgSize_ = 1024;

            /** local ip */
            std::string local_ip_ = "127.0.0.1";
            /** initialize the connection */
            int init_connection();
            /** handler for error logging */
            EzChat::ErrorHandler eHandler_;
            /** handler for low level functionality */
            EzChat::ClientMessageHandler mHandler_;
    };
}
#endif
