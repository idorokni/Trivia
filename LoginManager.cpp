#include "LoginManager.h"

LoginManager LoginManager::s_Instance;

bool LoginManager::signup(const std::string& password, const std::string& userName, const std::string& mail) {
	return true;
}
bool LoginManager::login(const std::string& password, const std::string& userName) {
	return true;
}
bool LoginManager::logout(const std::string& userName) {
	return true;
}

LoginManager& LoginManager::get() noexcept {
	return s_Instance;
}