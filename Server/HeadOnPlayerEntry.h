#pragma once
#include "LoggedUser.h"
#include "Question.h"

class HeadOnPlayerEntry {
private:
	LoggedUser _loggedUser;
	unsigned int _health;
	Question _lastQuestion;
	unsigned int _isWinner;

public:
	HeadOnPlayerEntry(const LoggedUser& loggedUser, unsigned int health, const Question& question);
	const LoggedUser& getLoggedUser();
	unsigned int getHealth();
	Question& getLastQuestion();
	unsigned int getIsWinner();
	void setLastQuestion(const Question& question);
	void setIsWinner();
	void setHealth(unsigned int health);
};