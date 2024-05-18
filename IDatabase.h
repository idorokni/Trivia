#pragma once
#include <iostream>

class IDatabase {
public:
    virtual ~IDatabase() = default;

    virtual bool open() = 0;
    virtual bool close() = 0;
    virtual int doesUserExist(const std::string& username) = 0;
    virtual int doesPasswordMatch(const std::string& username, const std::string& password) = 0;
    virtual int addNewUser(const std::string& username, const std::string& password, const std::string& email, const std::string& address, const std::string& phone, const std::string& birthday) = 0;

    virtual std::list<Question> getQuestions(const int number) = 0;
    virtual float getPlayerAverageAnswerTime(const std::string&) = 0;

    static IDatabase& get();
};