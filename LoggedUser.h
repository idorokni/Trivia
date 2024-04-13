#pragma once
#include<string>

class LoggedUser {
private:
	std::string m_username;
public:
	const std::string& getUsername() const noexcept;
};
