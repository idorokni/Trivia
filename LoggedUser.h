#pragma once
#include<string>

class LoggedUser {
private:
	std::string m_username;
public:
	LoggedUser(const std::string& userName);

	const std::string& getUsername() const noexcept;
};
