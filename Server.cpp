#include "Server.h"

void Server::run() {
	std::string choice;
	IDatabase::get().open();
	std::thread t_connector(&Communicator::startHandleRequest, std::ref(Communicator::get()));
	t_connector.detach();

	while (choice != "EXIT") {
		std::cin >> choice;
	}
}

Server& Server::get() noexcept {
	static Server s_Instance;
	return s_Instance;
}