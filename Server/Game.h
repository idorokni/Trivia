#pragma once
#include "Question.h"
#include "LoggedUser.h"
#include "Structs.h"
#include <map>
#include "IDatabase.h"

class Game
{
private:
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	unsigned int m_gameId;
	//unsigned int m_lastGivenQuestionId;
	void submitGameStatsToDB();

public:
	Game(const std::vector<Question>& questions, std::map<LoggedUser, GameData>& players, unsigned int gameId);
	Question getQuestionForUser(LoggedUser user);
	void submitAnswer(unsigned int answerId, unsigned int answerTime, LoggedUser player);
	void removePlayer(LoggedUser player);
	std::vector<PlayerResults> getGameResults(const LoggedUser& loggedUser);
	unsigned int getGameId() { return m_gameId; }
};