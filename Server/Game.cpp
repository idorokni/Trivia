#include "Game.h"

Game::Game(const std::vector<Question>& questions, std::map<LoggedUser, GameData>& players, unsigned int gameId)
{
	m_questions = questions;
	m_players = players;
	m_gameId = gameId;
	//m_lastGivenQuestionId = 0;
}

Question Game::getQuestionForUser(LoggedUser user)
{
	//m_lastGivenQuestionId++;
	m_players[user].lastGivenQuestionId++;
	return m_questions[m_players[user].lastGivenQuestionId - 1];
}

void Game::submitAnswer(unsigned int answerId, unsigned int answerTime, LoggedUser player)
{
	if (answerId == 1) m_players[player].correctAnswerCount++;
	else m_players[player].wrongAnswerCount++;
	m_players[player].averageAnswerTime = (m_players[player].averageAnswerTime + answerTime) / 2;
}

void Game::removePlayer(LoggedUser player)
{
	m_players.erase(player);
}

std::vector<PlayerResults> Game::getGameResults()
{
	std::vector<PlayerResults> results;
	for (std::pair<LoggedUser, GameData> player : m_players)
	{
		PlayerResults currentPlayerResult;
		currentPlayerResult.username = player.first.getUsername();
		currentPlayerResult.correctAnswerCounter = player.second.correctAnswerCount;
		currentPlayerResult.wrongAnswerCounter = player.second.wrongAnswerCount;
		currentPlayerResult.averageAnswerTime = player.second.averageAnswerTime;
		results.push_back(currentPlayerResult);
	}
	return results;
}

void Game::submitGameStatsToDB(GameData gameData)
{
	//IDatabase::get().
}
