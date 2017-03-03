#ifndef CLIENT_MESSAGE_HANDLER_H
#define CLIENT_MESSAGE_HANDLER_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdexcept>
#include <netdb.h>
#include "MessageHandler.h"


namespace EzChat {
    /**
     * @class ClientMessageHandler manages sending and receiving messages for clients
     * @author Arvin Sharma
     */
	class ClientMessageHandler : virtual public MessageHandler {
		public:
        /**
         * constructs a message with default values
         */
        ClientMessageHandler(){};
        /**
         * constructs a message
         * @param ip is the ip of this handler
         * @param msgSize is the max size of messages
         */
        ClientMessageHandler(std::string ip, int msgSize);
        /**
         * Sends the given message to the connected recipient
         * @param message is the message to send
         */
        virtual void sendMessage(std::string message) const noexcept;

        /**
         * determines if this handler is connected to the server
         * @return true if this handler is connected
         */
        virtual bool isConnected() const noexcept;
        /**
         * initializes the connection to the server
         */
        virtual void initializeConnection() noexcept;
        /**
         * creates a socket with the given port number for the server to connect to
         * @param port is the port of the server
         */
        virtual void createSocket(int port);
        /**
         * handles connecting to an address
         * @return 0 on success, negative number otherwise
         */
        virtual int handleConnect() noexcept;

        /**
         * Waits for a connection
         * @throw domain_error if this is called on a client
         * @return 0 on success, negative number otherwise
         */
        virtual int handleListen() {
            throw std::domain_error("don't call this in client");
            return -1;
        }

        /**
         * Binds this address to a socket.
         * suspends the process until a connection is established
         * @throw domain_error if this is called on a client
         */
        virtual bool couldNotBind() {
            throw std::domain_error("don't call this in client");
            return -1;
        }

        /**
         * Confirms if a connection was received
         * @return true if a connection has been established. Process is suspended until a connection is established
         */
        virtual bool confirmConnection() noexcept;


        /**
         * receives a message
         * @return the received message
         */
        virtual std::string handleReceive() noexcept;
        /**
         * closes this socket
         */
        virtual void handleClose() noexcept;

		private:
			/** The socket file descriptor for this handler */
			int fd_;

         	/** Server socket info */
            struct sockaddr_in server_address_;

            /** the ip of the server */
            std::string ip_;
            /** the max msg size */
            int msgSize_;

            /**
             * sends msg to server
             * @param buffer is the msg
             * @param size is the size of buffer
             */
            void handleSend(const char* buffer, int size) const noexcept;

	};
}
#endif

