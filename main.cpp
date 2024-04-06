#pragma comment(lib, "ws2_32.lib")

#include "WSAInitializer.h"
#include "Server.h"
#include "JsonResponsePacketSerializer.h"


int main() {
	try 
	{
		WSAInitializer wsaInit;
		LoginResponse l;
		l.status = 1;
		Buffer buff = JsonResponsePacketSerializer::serializeResponse(l);
		Server server;

		server.run();
	}
	catch (std::exception& e) 
	{
		std::cout << e.what() << std::endl;
	}



	return 0;
}