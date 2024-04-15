#include "SqliteDataBase.h"
#include "sqlite3.h"
#include <io.h>

IDatabase& IDatabase::get() {
	static SqliteDataBase instance;
	return instance;
}

SqliteDataBase::~SqliteDataBase() {
	IDatabase::get().close();
	this->_db = nullptr;
}

bool SqliteDataBase::open()
{
	std::string dbFileName = DATABASE_NAME;

	// Check if the DB exists
	int file_exist = _access(dbFileName.c_str(), 0);
	// Create DB if doesn't exist, or alternitavely opening it if it exists
	int res = sqlite3_open(dbFileName.c_str(), &(this->_db));
	if (res != SQLITE_OK) {
		this->_db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		return false;
	}
	if (file_exist != 0) // If the DB doesn't exist, we will now create it
	{
		//sql query
		const char* sqlStatement = "create table User (username integer primary key autoincrement not null, password text not null, email text not null);";

		char* errMessage = nullptr;
		res = sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage);
		if (res != SQLITE_OK)
			return false;
	}
	return true;
}

bool SqliteDataBase::close()
{
	// Closing connection
	int res = sqlite3_close(this->_db);
	if (res != SQLITE_OK) {
		std::cout << "Failed to close DB" << std::endl;
		return false;
	}
	this->_db = nullptr;
	return true;
}

int SqliteDataBase::doesUserExist(const std::string& username)
{
	std::string sqlString = "select * from User where username = '" + username + "';";
	const char* sqlStatement = sqlString.c_str();
	int res = 0, exists = 0;
	char* errMessage = nullptr;

	// Trying to get the user by his username.
	// If the variable 'exists' = 0, it means that no user with this username was found therefore it doesn't exist. Otherwise, it exists and we will return 1.
	res = sqlite3_exec(this->_db, sqlStatement, callbackGetUser, &exists, &errMessage);
	if (res != SQLITE_OK)
		std::cout << "one of the given parameters is wrong.";
	return exists;
}

int SqliteDataBase::doesPasswordMatch(const std::string& username, const std::string& password)
{
	std::string sqlString = "select * from User where username = '" + username + "' and password = '" + password + ";";
	const char* sqlStatement = sqlString.c_str();
	int res = 0, matches = 0;
	char* errMessage = nullptr;

	// Trying to get the user by his username.
	// If the variable 'matches' = 0, it means that no user with this username and this password was found therefore the password doesn't match. Otherwise, it matches and we will return 1.
	res = sqlite3_exec(this->_db, sqlStatement, callbackGetUser, &matches, &errMessage);
	if (res != SQLITE_OK)
		std::cout << "one of the given parameters is wrong.";
	return matches;
}

int SqliteDataBase::addNewUser(const std::string& username, const std::string& password, const std::string& email)
{
	std::string sqlString = "insert into User (username, password, email) values (" + username + ", '" + password + ", '" + email + "');";
	const char* sqlStatement = sqlString.c_str();
	int res = 0;
	char* errMessage = nullptr;

	// Adding a user to the users table with an sql statement
	res = sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << "one of the given parameters is wrong.";
		return -1;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// CallBacks ///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

int SqliteDataBase::callbackGetUser(void* data, int argc, char** argv, char** azColName)
{
	int* exists = static_cast<int*>(data);

	for (int i = 0; i < argc; i++) 
	{
		if (std::string(azColName[i]) == "username") *exists = 1;
	}

	return 0;
}