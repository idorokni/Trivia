#pragma once
#include "LoggedUser.h"
#include "Structs.h"
#include <map>
#include "IDatabase.h"

class Game
{
protected:
	unsigned int m_gameId;
	void submitGameStatsToDB(const GameData& gameData, const LoggedUser& player);

public:
	unsigned int getGameId() { return m_gameId; }
	virtual Question getQuestionForUser(LoggedUser user) = 0;
	virtual void submitAnswer(unsigned int answerId, unsigned int answerTime, LoggedUser player) = 0;
	virtual void removePlayer(LoggedUser player) = 0;
	virtual std::vector<PlayerResults> getGameResults(const LoggedUser& loggedUser) = 0;
};