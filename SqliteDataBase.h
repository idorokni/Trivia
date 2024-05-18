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

public:
    ~SqliteDataBase();

    bool open() override;
    bool close() override;
    int doesUserExist(const std::string& username) override;
    int doesPasswordMatch(const std::string& username, const std::string& password) override;
    int addNewUser(const std::string& username, const std::string& password, const std::string& email, const std::string& address, const std::string& phone, const std::string& birthday);
    
    std::list<Question> getQuestions(const int number) override;
    virtual float getPlayerAverageAnswerTime(const std::string&) override;

    static IDatabase& get();
};