#pragma once
#include <vector>
#include "LoggedUser.h"
#include "Structs.h"

class Room {
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
public:
	void addUser(const LoggedUser& loggedUser);
	void removeUser(const LoggedUser& loggedUser);
	const std::vector<std::string>& getAllUsers() const;
};