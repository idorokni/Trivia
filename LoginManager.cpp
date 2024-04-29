#include "LoginManager.h"
#include "SqliteDataBase.h"

bool LoginManager::signup(const std::string& password, const std::string& userName, const std::string& mail, const std::string& address, const std::string& phone, const std::string& birthday)
{
	// Adding the user using the addNewUser from the dataBase class
	if (std::regex_search(password, std::regex(PASSWORD_REGEX_PATTERN)) && std::regex_search(mail, std::regex(EMAIL_REGEX_PATTERN)) && std::regex_search(address, std::regex(ADDRESS_REGEX_PATTERN)) && std::regex_search(phone, std::regex(PHONE_REGEX_PATTERN)) && std::regex_search(birthday, std::regex(BIRTHDAY_REGEX_PATTERN)) && IDatabase::get().addNewUser(userName, password, mail, address, phone, birthday) == 0) return login(password, userName);
	else return false;
}

bool LoginManager::login(const std::string& password, const std::string& userName) 
{
	// Adding the user to the list of the logged user, after checking this user exists and its passwords matches
	if (IDatabase::get().doesUserExist(userName) == 1 && IDatabase::get().doesPasswordMatch(userName, password) == 1)
	{
		// Checking if this user is already looged
		for (auto& loggedUser : this->m_loggedUsers)
		{
			if (loggedUser.getUsername() == userName) return false;
		}
		this->m_loggedUsers.emplace_back(userName);
		return true;
	}
	else return false;
}

bool LoginManager::logout(const std::string& userName) 
{
	if (IDatabase::get().doesUserExist(userName) == 1)
	{
		// Going over each LoggedUser in the vector of the logged users to check if it the user to erase
		for (auto it = m_loggedUsers.begin(); it != m_loggedUsers.end(); it++) 
		{
			if (it->getUsername() == userName)
			{
				// Erasing the LoggedUser with matching username
				it = this->m_loggedUsers.erase(it);
				return true;
			}
		}
		// Theoretically, don't supposed to get to this line because we made sure that the user we want to logout does exist
		return false;
	}
	else return false;
}

LoginManager& LoginManager::get() noexcept {
	static LoginManager s_Instance;
	return s_Instance;
}