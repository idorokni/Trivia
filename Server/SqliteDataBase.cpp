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
			"insert into Question (id, question, correct, ans1, ans2, ans3) VALUES (1, 'capital of Israel?', 'Jerusalem', 'Ashdod', 'Berlin', 'New York');"
			"insert into Question (id, question, correct, ans1, ans2, ans3) VALUES (2, 'capital of Germany?', 'Berlin', 'Paris', 'Hamburg', 'New York');"
			"insert into Question (id, question, correct, ans1, ans2, ans3) VALUES (3, 'capital of USA?', 'Washington', 'New York', 'San Diego', 'Los Santos');"
			"insert into Question (id, question, correct, ans1, ans2, ans3) VALUES (4, 'capital of Russia?', 'Moscow', 'Sain petersburg', 'Krasnoyarsk', 'Dagistan');"
			"insert into Question (id, question, correct, ans1, ans2, ans3) VALUES (5, 'capital of Ukraine?', 'Kiev', 'Oddessa', 'Kishinev', 'London');"
			"insert into Question (id, question, correct, ans1, ans2, ans3) VALUES (6, 'capital of France?', 'Paris', 'Monaco', 'Sen', 'Lyos');"
			"insert into Question (id, question, correct, ans1, ans2, ans3) VALUES (7, 'capital of Italy?', 'Rome', 'Napoly', 'Firenze', 'Milano');"
			"insert into Question (id, question, correct, ans1, ans2, ans3) VALUES (8, 'capital of Egypt?', 'Cairo', 'Alexandria', 'Taba', 'Sharem A Sehich');"
			"insert into Question (id, question, correct, ans1, ans2, ans3) VALUES (9, 'capital of Jordan?', 'Amman', 'Baku', 'Akabba', 'Damascus');"
			"insert into Question (id, question, correct, ans1, ans2, ans3) VALUES (10, 'capital of Lebanon?', 'Beirut', 'Tzur', 'Baalback', 'Tziddon');";

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
	const char* sql = "SELECT question, correct, ans1, ans2, ans3 FROM Question ORDER BY RANDOM() LIMIT ?;";
	//const char* sql = "SELECT question, correct, ans1, ans2, ans3 FROM Question LIMIT ?;";
	sqlite3_stmt* stmt;
	std::list<Question> questions;

	// Prepare the SQL statement
	if (sqlite3_prepare_v2(this->_db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
		// Bind the number parameter to the SQL statement
		sqlite3_bind_int(stmt, 1, number);

		// Execute the statement and retrieve the rows
		while (sqlite3_step(stmt) == SQLITE_ROW) 
		{
			const unsigned char* questionText = sqlite3_column_text(stmt, 0);
			const unsigned char* correctText = sqlite3_column_text(stmt, 1);
			const unsigned char* ans1Text = sqlite3_column_text(stmt, 2);
			const unsigned char* ans2Text = sqlite3_column_text(stmt, 3);
			const unsigned char* ans3Text = sqlite3_column_text(stmt, 4);

			std::vector<std::string> answers = { reinterpret_cast<const char*>(correctText), reinterpret_cast<const char*>(ans1Text), reinterpret_cast<const char*>(ans2Text), reinterpret_cast<const char*>(ans3Text) };
			//Question question = Question(reinterpret_cast<const char*>(questionText), answers);
			questions.emplace_back(reinterpret_cast<const char*>(questionText), answers);
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
	const char* sql = "SELECT username, score FROM Statistics ORDER BY score DESC LIMIT 5;";
	sqlite3_stmt* stmt;
	std::vector<std::string> topScores;

	// Prepare the SQL statement
	if (sqlite3_prepare_v2(this->_db, sql, -1, &stmt, nullptr) == SQLITE_OK)
	{
		// Execute the statement and retrieve the top five scores with usernames
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			const char* username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
			int score = sqlite3_column_int(stmt, 1);

			// Format the result as "username - score" and add to the vector
			topScores.push_back(std::string(username) + "-" + std::to_string(score));
		}

		// Finalize the statement
		sqlite3_finalize(stmt);
	}
	else {
		std::cerr << "Error preparing statement: " << sqlite3_errmsg(this->_db) << std::endl;
	}

	return topScores;
}

bool SqliteDataBase::addQuestion(const std::string& question, const std::string& correctAnswer, const std::string& wrongAnswer1, const std::string& wrongAnswer2, const std::string& wrongAnswer3)
{
	const char* sql = "INSERT INTO Question (question, correct, ans1, ans2, ans3) VALUES (?, ?, ?, ?, ?);";
	sqlite3_stmt* stmt;
	int res;

	// Preparing the SQL statement.
	res = sqlite3_prepare_v2(this->_db, sql, -1, &stmt, nullptr);
	if (res != SQLITE_OK) {
		std::cerr << "Error preparing statement: " << sqlite3_errmsg(this->_db) << std::endl;
		return false;
	}

	// Binding the parameters.
	sqlite3_bind_text(stmt, 1, question.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, correctAnswer.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, wrongAnswer1.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 4, wrongAnswer2.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 5, wrongAnswer3.c_str(), -1, SQLITE_STATIC);

	// Executing the SQL statement.
	res = sqlite3_step(stmt);
	if (res != SQLITE_DONE) {
		std::cerr << "Error executing statement: " << sqlite3_errmsg(this->_db) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	// Finalizing the SQL statement.
	sqlite3_finalize(stmt);
	return true;
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

int SqliteDataBase::submitGameStatistics(const GameData& gameData, const LoggedUser& loggedUser) {
	const char* sqlCheck = "select 1 from Statistics where username = ? limit 1;";
	const char* updateQuery = "update statistics set num_correct_answers = ((select num_correct_answers from statistics where username = ?) + ?), avg_time_per_question = (((select avg_time_per_question from statistics where username = ?) + ?) / 2), num_of_total_answers = (select num_of_total_answers from statistics where username = ?) + ? + ?, num_of_total_games = (select num_of_total_games from statistics where username = ?) + 1, score = (select score from statistics where username = ?) + ? where username = ?;";
	const char* insertQuery = "insert into statistics (username, num_correct_answers, avg_time_per_question, num_of_total_answers, num_of_total_games, score) values (?, ?, ?, ? + ?, 1, ?);";
	sqlite3_stmt* stmtCheck;
	sqlite3_stmt* stmtUpdate;
	sqlite3_stmt* stmtInsert;
	int res = 1;

	if (sqlite3_prepare_v2(this->_db, sqlCheck, -1, &stmtCheck, nullptr) == SQLITE_OK) {
		sqlite3_bind_text(stmtCheck, 1, loggedUser.getUsername().c_str(), -1, SQLITE_STATIC);

		if (sqlite3_step(stmtCheck) == SQLITE_ROW) {
			if (sqlite3_prepare_v2(this->_db, updateQuery, -1, &stmtUpdate, nullptr) == SQLITE_OK) {
				sqlite3_bind_text(stmtUpdate, 1, loggedUser.getUsername().c_str(), -1, SQLITE_STATIC);
				sqlite3_bind_int(stmtUpdate, 2, gameData.correctAnswerCount);
				sqlite3_bind_text(stmtUpdate, 3, loggedUser.getUsername().c_str(), -1, SQLITE_STATIC);
				sqlite3_bind_double(stmtUpdate, 4, gameData.averageAnswerTime);
				sqlite3_bind_text(stmtUpdate, 5, loggedUser.getUsername().c_str(), -1, SQLITE_STATIC);
				sqlite3_bind_int(stmtUpdate, 6, gameData.correctAnswerCount);
				sqlite3_bind_int(stmtUpdate, 7, gameData.wrongAnswerCount);
				sqlite3_bind_text(stmtUpdate, 8, loggedUser.getUsername().c_str(), -1, SQLITE_STATIC);
				sqlite3_bind_text(stmtUpdate, 9, loggedUser.getUsername().c_str(), -1, SQLITE_STATIC);
				sqlite3_bind_int(stmtUpdate, 10, gameData.correctAnswerCount);
				sqlite3_bind_text(stmtUpdate, 11, loggedUser.getUsername().c_str(), -1, SQLITE_STATIC);

				if (sqlite3_step(stmtUpdate) != SQLITE_DONE) {
					std::cerr << "Error executing statement: " << sqlite3_errmsg(this->_db) << std::endl;
					res = 0; // Return error code
				}

				sqlite3_finalize(stmtUpdate);
			}
			else
			{
				std::cerr << "Error preparing statement: " << sqlite3_errmsg(this->_db) << std::endl;
				res = 0;
			}
		}
		else {
			if (sqlite3_prepare_v2(this->_db, insertQuery, -1, &stmtInsert, nullptr) == SQLITE_OK) {
				sqlite3_bind_text(stmtInsert, 1, loggedUser.getUsername().c_str(), -1, SQLITE_STATIC);
				sqlite3_bind_int(stmtInsert, 2, gameData.correctAnswerCount);
				sqlite3_bind_double(stmtInsert, 3, gameData.averageAnswerTime);
				sqlite3_bind_int(stmtInsert, 4, gameData.correctAnswerCount);
				sqlite3_bind_int(stmtInsert, 5, gameData.wrongAnswerCount);
				sqlite3_bind_int(stmtInsert, 6, gameData.correctAnswerCount);

				if (sqlite3_step(stmtInsert) != SQLITE_DONE) {
					std::cerr << "Error executing statement: " << sqlite3_errmsg(this->_db) << std::endl;
					res = 0; // Return error code
				}

				sqlite3_finalize(stmtInsert);
			}
			else
			{
				std::cerr << "Error preparing statement: " << sqlite3_errmsg(this->_db) << std::endl;
				res = 0;
			}
		}

		sqlite3_finalize(stmtCheck);
	}
	else {
		std::cerr << "Error preparing statement: " << sqlite3_errmsg(this->_db) << std::endl;
		res = 0;
	}

	return res;
}