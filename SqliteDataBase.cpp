#include "SqliteDataBase.h"
#include "sqlite3.h"
#include <io.h>
#include <string>

IDatabase& IDatabase::get()
{
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
		const char* sqlStatement = "create table User (username text primary key not null, password text not null, email text not null, address text not null, phone text not null, birthday text not null);"
			"create table Question (id integer primary key not null, question text not null, correct text not null, ans1 text not null, ans2 text not null, ans3 text not null);"
			"create table Statistics (username text primary key not null, num_correct_answers integer not null, avg_time_per_question real not null, num_of_total_answers integer not null, num_of_total_games integer not null, score integer not null);"
			"insert into Question (id, question, correct) VALUES (1, 'capital of Israel?', 'Jerusalem', 'Ashdod', 'Berlin', 'New York');"
			"insert into Question (id, question, correct) VALUES (2, 'capital of Germany?', 'Berlin', 'Paris', 'Hamburg', 'New York');"
			"insert into Question (id, question, correct) VALUES (3, 'capital of USA?', 'Washington', 'New York', 'San Diego', 'Los Santos');"
			"insert into Question (id, question, correct) VALUES (4, 'capital of Russia?', 'Moscow', 'Sain petersburg', 'Krasnoyarsk', 'Dagistan');"
			"insert into Question (id, question, correct) VALUES (5, 'capital of Ukraine?', 'Kiev', 'Oddessa', 'Kishinev', 'London');"
			"insert into Question (id, question, correct) VALUES (6, 'capital of France?', 'Paris', 'Monaco', 'Sen', 'Lyos');"
			"insert into Question (id, question, correct) VALUES (7, 'capital of Italy?', 'Rome', 'Napoly', 'Firenze', 'Milano');"
			"insert into Question (id, question, correct) VALUES (8, 'capital of Egypt?', 'Cairo', 'Alexandria', 'Taba', 'Sharem A Sehich');"
			"insert into Question (id, question, correct) VALUES (9, 'capital of Jordan?', 'Amman', 'Baku', 'Akabba', 'Damascus');"
			"insert into Question (id, question, correct) VALUES (10, 'capital of Lebanon?', 'Beirut', 'Tzur', 'Baalback', 'Tziddon');";

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

std::list<Question> SqliteDataBase::getQuestions(const int number) 
{
	const char* sql = "SELECT id, question, correct FROM Question LIMIT ?;";
	sqlite3_stmt* stmt;
	std::list<Question> questions;

	// Prepare the SQL statement
	if (sqlite3_prepare_v2(this->_db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
		// Bind the number parameter to the SQL statement
		sqlite3_bind_int(stmt, 1, number);

		// Execute the statement and retrieve the rows
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			int id = sqlite3_column_int(stmt, 0);
			const unsigned char* questionText = sqlite3_column_text(stmt, 1);
			const unsigned char* correctText = sqlite3_column_text(stmt, 2);

			questions.emplace_back(id, reinterpret_cast<const char*>(questionText), reinterpret_cast<const char*>(correctText));
		}

		// Finalize the statement
		sqlite3_finalize(stmt);
	}
	else {
		std::cerr << "Error preparing statement: " << sqlite3_errmsg(this->_db) << std::endl;
	}

	return questions;
}

float SqliteDataBase::getPlayerAverageAnswerTime(const std::string& username) 
{
	const char* sql = "SELECT avg_time_per_question FROM Statistics WHERE username = ?;";
	sqlite3_stmt* stmt;
	float avgTime = 0.0;

	// Prepare the SQL statement
	if (sqlite3_prepare_v2(this->_db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
		// Bind the username parameter to the SQL statement
		sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

		// Execute the statement and retrieve the average time
		if (sqlite3_step(stmt) == SQLITE_ROW) avgTime = static_cast<float>(sqlite3_column_double(stmt, 0));

		// Finalize the statement
		sqlite3_finalize(stmt);
	}
	else std::cerr << "Error preparing statement: " << sqlite3_errmsg(this->_db) << std::endl;

	return avgTime;
}

int SqliteDataBase::getNumOfCorrectAnswers(const std::string& username)
{
	const char* sql = "SELECT num_correct_answers FROM Statistics WHERE username = ?;";
	return getColumn(sql, username);
}

int SqliteDataBase::getNumOfTotalAnswers(const std::string& username)
{
	const char* sql = "SELECT num_of_total_answers FROM Statistics WHERE username = ?;";
	return getColumn(sql, username);
}

int SqliteDataBase::getNumOfPlayerGames(const std::string& username)
{
	const char* sql = "SELECT num_of_total_games FROM Statistics WHERE username = ?;";
	return getColumn(sql, username);
}

int SqliteDataBase::getPlayerScore(const std::string& username)
{
	const char* sql = "SELECT score FROM Statistics WHERE username = ?;";
	return getColumn(sql, username);
}

std::vector<std::string> SqliteDataBase::getHighScores()
{
	const char* sql = "SELECT score FROM Statistics ORDER BY score DESC LIMIT 5;";
	sqlite3_stmt* stmt;
	std::vector<std::string> topScores;

	// Prepare the SQL statement
	if (sqlite3_prepare_v2(this->_db, sql, -1, &stmt, nullptr) == SQLITE_OK) 
	{
		// Execute the statement and retrieve the top five scores
		while (sqlite3_step(stmt) == SQLITE_ROW) 
		{
			int score = sqlite3_column_int(stmt, 0);
			topScores.push_back(std::to_string(score));
		}

		// Finalize the statement
		sqlite3_finalize(stmt);
	}
	else {
		std::cerr << "Error preparing statement: " << sqlite3_errmsg(this->_db) << std::endl;
	}

	return topScores;
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

int SqliteDataBase::getColumn(const char* sql, const std::string& username)
{
	sqlite3_stmt* stmt;
	int column = 0;

	// Prepare the SQL statement
	if (sqlite3_prepare_v2(this->_db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
		// Bind the username parameter to the SQL statement
		sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

		// Execute the statement and retrieve the column
		if (sqlite3_step(stmt) == SQLITE_ROW) column = static_cast<float>(sqlite3_column_int(stmt, 0));

		// Finalize the statement
		sqlite3_finalize(stmt);
	}
	else std::cerr << "Error preparing statement: " << sqlite3_errmsg(this->_db) << std::endl;

	return column;
}