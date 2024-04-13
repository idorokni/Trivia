#pragma once

#include <vector>
#include "IDatabase.h"
#include "LoggedUser.h"

class LoginManager {
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
public:
	void signup(const std::string& password, const std::string& userName, const std::string& mail);
	void login(const std::string& password, const std::string& userName);
	void logout(const std::string& userName);
};