#include "Room.h"

void Room::addUser(const LoggedUser& loggedUser) {
	m_users.emplace_back(loggedUser.getUsername());
}
void Room::removeUser(const LoggedUser& loggedUser) {
	for (auto it = m_users.begin(); it < m_users.end(); it++) {
		if (it->getUsername() == loggedUser.getUsername()) {
			m_users.erase(it);
		}
	}
}
const std::vector<std::string>& Room::getAllUsers() const {
	std::vector<std::string> allUsers;
	for (auto user : m_users) {
		allUsers.emplace_back(user.getUsername());
	}

	return allUsers;
}