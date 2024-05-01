#pragma once
#include <WinSock2.h>
#include <map>
#include <string>
#include <iostream>
#include <thread>
#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

#define PORT 8326

class Communicator {
public:
	void startHandleRequest();

	static Communicator& get() noexcept;

private:
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;

	void bindAndListen();
	void handleNewClient(SOCKET sock);
};
