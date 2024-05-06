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
		const char* sqlStatement = "create table User (username text primary key not null, password text not null, email text not null, address text not null, phone text not null, birthday text not null);";

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
	const char* sql = "select 1 from User where username = ? limit 1;";
	sqlite3_stmt* stmt;
	int exists = 0;

	// Trying to get the user by his username.
	// If the variable 'exists' = 0, it means that no user with this username was found therefore it doesn't exist. Otherwise, it exists and we will return 1.
	if (sqlite3_prepare_v2(this->_db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

		if (sqlite3_step(stmt) == SQLITE_ROW) {
			exists = 1;
		}

		sqlite3_finalize(stmt);
	}
	else {
		std::cerr << "Error preparing statement: " << sqlite3_errmsg(this->_db) << std::endl;
	}

	return exists;
}

int SqliteDataBase::doesPasswordMatch(const std::string& username, const std::string& password)
{
	const char* sql = "SELECT 1 FROM User WHERE username = ? AND password = ? LIMIT 1;";
	sqlite3_stmt* stmt;
	int matches = 0;

	// Trying to get the user by his username.
	// If the variable 'matches' = 0, it means that no user with this username and this password was found therefore the password doesn't match. Otherwise, it matches and we will return 1.
	if (sqlite3_prepare_v2(this->_db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

		if (sqlite3_step(stmt) == SQLITE_ROW) {
			matches = 1;
		}

		sqlite3_finalize(stmt);
	}
	else {
		std::cerr << "Error preparing statement: " << sqlite3_errmsg(this->_db) << std::endl;
	}

	return matches;
}

int SqliteDataBase::addNewUser(const std::string& username, const std::string& password, const std::string& email, const std::string& address, const std::string& phone, const std::string& birthday)
{
	const char* sql = "INSERT INTO User (username, password, email, address, phone, birthday) VALUES (?, ?, ?, ?, ?, ?);";
	sqlite3_stmt* stmt;
	int res = 0;

	if (sqlite3_prepare_v2(this->_db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
		// Bind parameters to the prepared statement
		sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, email.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 4, address.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 5, phone.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 6, birthday.c_str(), -1, SQLITE_STATIC);

		// Execute the prepared statement to insert the new user
		if (sqlite3_step(stmt) != SQLITE_DONE) {
			std::cerr << "Error executing statement: " << sqlite3_errmsg(this->_db) << std::endl;
			res = -1; // Return error code
		}

		sqlite3_finalize(stmt); // Finalize the statement
	}
	else {
		std::cerr << "Error preparing statement: " << sqlite3_errmsg(this->_db) << std::endl;
		res = -1; // Return error code
	}

	return res;
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