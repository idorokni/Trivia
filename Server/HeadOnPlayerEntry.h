#pragma once
#include "LoggedUser.h"
#include "Question.h"

class HeadOnPlayerEntry {
private:
	LoggedUser _loggedUser;
	int _health;
	Question _lastQuestion;
	unsigned int _isWinner;

public:
	HeadOnPlayerEntry(const LoggedUser& loggedUser, int health, const Question& question);
	const LoggedUser& getLoggedUser();
	int getHealth();
	Question& getLastQuestion();
	unsigned int getIsWinner();
	void setLastQuestion(const Question& question);
	void setIsWinner();
	void setHealth(int health);
};