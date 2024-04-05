#pragma once
#include <WinSock2.h>
#include <map>
#include <string>
#include <iostream>
#include <thread>
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"

#define PORT 8326

class Communicator {
public:
	void startHandleRequest();

private:
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;

	void bindAndListen();
	void handleNewClient(SOCKET sock);
};
