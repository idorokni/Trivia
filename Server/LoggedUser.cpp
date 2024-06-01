#include "LoggedUser.h"

const std::string& LoggedUser::getUsername() const noexcept{
	return this->m_username;
}

LoggedUser::LoggedUser(const std::string& userName) {
	m_username = userName;
}
