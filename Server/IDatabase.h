#pragma once
#include <iostream>
#include "Question.h"
#include "Structs.h"
#include "LoggedUser.h"
#include <list>

class IDatabase {
public:
    virtual ~IDatabase() = default;

    virtual bool open() = 0;
    virtual bool close() = 0;
    virtual int doesUserExist(const std::string& username) = 0;
    virtual int doesPasswordMatch(const std::string& username, const std::string& password) = 0;
    virtual int addNewUser(const std::string& username, const std::string& password, const std::string& email, const std::string& address, const std::string& phone, const std::string& birthday) = 0;

    virtual std::list<Question> getQuestions(const int number) = 0;
    virtual float getPlayerAverageAnswerTime(const std::string& username) = 0;
    virtual int getNumOfCorrectAnswers(const std::string& username) = 0;
    virtual int getNumOfTotalAnswers(const std::string& username) = 0;
    virtual int getNumOfPlayerGames(const std::string& username) = 0;
    virtual int getPlayerScore(const std::string& username) = 0;
    virtual std::vector<std::string> getHighScores() = 0;
    virtual int submitGameStatistics(const GameData& gameData, const LoggedUser& loggedUser) = 0;

    static IDatabase& get();
};