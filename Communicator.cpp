#include "Communicator.h"
#define HELLO_LEN 5

Communicator& Communicator::get() noexcept {
	static Communicator s_Instance;
	return s_Instance;
}

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
		LoginRequestHandler* client_login_request = RequestHandlerFactory::get().createLoginRequestHandler();
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
	try {
		while (true) {
			Buffer buff;
			buff.resize(HEADER_LENGTH);
			int res = recv(sock, (char*)&buff.at(0), HEADER_LENGTH, 0);
			if (res == INVALID_SOCKET)
			{
				std::string s = "Error while recieving from socket: " + sock;

				throw std::exception(s.c_str());
			}
			uint32_t length;
			std::memcpy(&length, &buff.at(CODE_AMOUNT_BYTES), BYTES_LENGTH);
			buff.resize(HEADER_LENGTH + length);
			res = recv(sock, (char*)&buff.at(HEADER_LENGTH), length, 0);
			if (res == INVALID_SOCKET)
			{
				std::string s = "Error while recieving from socket: ";
				s += std::to_string(sock);
				throw std::exception(s.c_str());
			}

			RequestInfo info;
			info.id = (RequestCode)buff.at(0);
			info.buff = std::move(buff);
			info.recivalTime = std::time(nullptr);
			if (this->m_clients[sock]->isRequestRelevant(info)) {
				RequestResult reasult = this->m_clients.at(sock)->handleRequest(info);
				if (reasult.newHandler != this->m_clients.at(sock)) {
					delete this->m_clients.at(sock);
					this->m_clients.at(sock) = reasult.newHandler;
				}
				if (send(sock, std::string(reasult.response.begin(), reasult.response.end()).c_str(), reasult.response.size(), 0) == INVALID_SOCKET){
					throw std::exception("Error while sending message to client");
				}
			}
			else
			{
				RequestResult reasult;
				reasult.newHandler = nullptr;
				ErrorResponse errResponse;
				errResponse.msg = "request code isn't proper!";
				reasult.response = JsonResponsePacketSerializer::serializeResponse(errResponse);
				if (send(sock, std::string(reasult.response.begin(), reasult.response.end()).c_str(), reasult.response.size(), 0) == INVALID_SOCKET) {
					throw std::exception("Error while sending message to client");
				}
			}
		}
	}
	catch (const std::exception& e) {
		this->m_clients.erase(sock);
	}
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

