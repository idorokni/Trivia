#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include "Constants.h"
#include <list>
#include "Question.h"

class SqliteDataBase : public IDatabase
{
private:
    sqlite3* _db;
    static int callbackGetUser(void* data, int argc, char** argv, char** azColName);
    int getColumn(const char* sql, const std::string& username);

public:
    ~SqliteDataBase();

    bool open() override;
    bool close() override;
    int doesUserExist(const std::string& username) override;
    int doesPasswordMatch(const std::string& username, const std::string& password) override;
    int addNewUser(const std::string& username, const std::string& password, const std::string& email, const std::string& address, const std::string& phone, const std::string& birthday);
    
    std::list<Question> getQuestions(const int number) override;
    float getPlayerAverageAnswerTime(const std::string& username) override;
    int getNumOfCorrectAnswers(const std::string& username) override;
    int getNumOfTotalAnswers(const std::string& username) override;
    int getNumOfPlayerGames(const std::string& username) override;
    int getPlayerScore(const std::string& username) override;
    std::vector<std::string> getHighScores() override;


    static IDatabase& get();
};