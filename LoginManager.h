#pragma once

#include <vector>
#include <regex>
#include "IDatabase.h"
#include "LoggedUser.h"
#include "Constants.h"

class LoginManager {
private:
	std::vector<LoggedUser> m_loggedUsers;

public:
	bool signup(const std::string& password, const std::string& userName, const std::string& mail, const std::string& address, const std::string& phone, const std::string& birthday);
	bool login(const std::string& password, const std::string& userName);
	bool logout(const std::string& userName);

	static LoginManager& get() noexcept;
};