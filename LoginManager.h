#pragma once

#include <vector>
#include "IDatabase.h"
#include "LoggedUser.h"

class LoginManager {
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;

	static LoginManager s_Instance;
public:
	bool signup(const std::string& password, const std::string& userName, const std::string& mail);
	bool login(const std::string& password, const std::string& userName);
	bool logout(const std::string& userName);

	static LoginManager& get() noexcept;
};