#include "Communicator.h"
#define HELLO_LEN 5

void Communicator::startHandleRequest() {
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	this->m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (this->m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");

	bindAndListen();

	// accpeting new clients
	while (true) {
		SOCKET client_socket = accept(this->m_serverSocket, NULL, NULL);
		if (client_socket == INVALID_SOCKET)
			return;

		// adding new client to the clients map
		LoginRequestHandler* client_login_request = new LoginRequestHandler();
		this->m_clients[client_socket] = client_login_request;
		std::cout << "Client accepted. Server and client can speak" << std::endl;
		try
		{
			std::thread clientThread(&Communicator::handleNewClient, this, client_socket);
			clientThread.detach();
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

void Communicator::handleNewClient(SOCKET sock) {
	// sending a welcome message
	std::string message = "Hello";
	const char* dataToSend = message.c_str();
	if (send(sock, dataToSend, message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}

	// recieving a response message
	char* dataToRecv = new char[HELLO_LEN + 1];
	int res = recv(sock, dataToRecv, HELLO_LEN, 0);

	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sock);
		throw std::exception(s.c_str());
	}
	*(dataToRecv + HELLO_LEN) = 0;
	std::cout << dataToRecv << std::endl;

	// erasing client from the clients map when the connection is done
	this->m_clients.erase(sock);
}

void Communicator::bindAndListen() {

	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(this->m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(this->m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << PORT << std::endl;
}

