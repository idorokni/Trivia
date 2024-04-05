#include "Server.h"

void Server::run() {
	std::string choice;
	std::thread t_connector(&Communicator::startHandleRequest, std::ref(this->m_communicator));
	t_connector.detach();

	while (choice != "EXIT") {
		std::cin >> choice;
	}
}