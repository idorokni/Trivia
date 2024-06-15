#pragma once
#include<string>

class LoggedUser {
private:
	std::string m_username;
public:
	LoggedUser() = default;
	LoggedUser(const std::string& userName);
	bool operator<(const LoggedUser& other) const {
		return m_username < other.m_username; // Compare based on username (or any other criteria)
	}
	const std::string& getUsername() const noexcept;
};
