#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <iostream>
#include <vector>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>

namespace EzChat {
    /**
     * Represents a Handler for sending and
     * receiving Messages over the internet
     * @author Arvin Sharma
     */
    class MessageHandler {
    public:

        /**
         * constructs a message with default values
         */
        MessageHandler(){};
        /**
         * constructs a message
         * @param ip is the ip of this handler
         * @param msgSize is the max size of messages
         */
        MessageHandler(std::string ip, int msgSize);
        /**
         * Sends the given message to the connected recipient
         * @param message is the message to send
         */
        virtual void sendMessage(std::string message) const noexcept = 0;

        /**
         * determines if this handler is connected to the server
         * @return true if this handler is connected
         */
        virtual bool isConnected() const noexcept = 0;
        /**
         * initializes the connection to the server
         */
        virtual void initializeConnection() noexcept = 0;
        /**
         * creates a socket with the given port number for the server to connect to
         * @param port is the port of the server
         * @throw domain_error if this is called on client
         */
        virtual void createSocket(int port) = 0;
        /**
         * handles connecting to an address
         * @return 0 on success, negative number otherwise
         */
        virtual int handleConnect() noexcept = 0;

        /**
         * Waits for a connection
         * @throw domain_error if this is called on a client
         * @return 0 on success, negative number otherwise
         */
        virtual int handleListen() = 0;

        /**
         * Binds this address to a socket.
         * suspends the process until a connection is established
         * @throw domain_error if this is called on a client
         */
        virtual bool couldNotBind() = 0;

        /**
         * Confirms if a connection was received
         * @return true if a connection has been established. Process is suspended until a connection is established
         */
        virtual bool confirmConnection() noexcept = 0;


        /**
         * receives a message
         * @return the received message
         */
        virtual std::string handleReceive() noexcept = 0;
        /**
         * closes this socket
         */
        virtual void handleClose() noexcept = 0;
    };

}
#endif
