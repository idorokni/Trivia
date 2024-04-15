#include "Server.h"

void Server::run() {
	std::string choice;
	IDatabase::get().open();
	std::thread t_connector(&Communicator::startHandleRequest, std::ref(this->m_communicator));
	t_connector.detach();

	while (choice != "EXIT") {
		std::cin >> choice;
	}
}