#pragma comment(lib, "ws2_32.lib")

#include "WSAInitializer.h"
#include "Server.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"


int main() {
	try 
	{
		WSAInitializer wsaInit;
		Server server;

		server.run();
	}
	catch (std::exception& e) 
	{
		std::cout << e.what() << std::endl;
	}



	return 0;
}