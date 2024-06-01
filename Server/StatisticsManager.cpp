#include "StatisticsManager.h"
#include <string>

std::vector<std::string> StatisticsManager::getHighScore() 
{
    return IDatabase::get().getHighScores();
}

std::vector<std::string> StatisticsManager::getUserStatistics(const std::string& username) 
{
    std::vector<std::string> statistics;
    statistics.push_back(std::to_string(IDatabase::get().getPlayerAverageAnswerTime(username)));
    statistics.push_back(std::to_string(IDatabase::get().getNumOfCorrectAnswers(username)));
    statistics.push_back(std::to_string(IDatabase::get().getNumOfTotalAnswers(username)));
    statistics.push_back(std::to_string(IDatabase::get().getNumOfPlayerGames(username)));
    return statistics;
}

StatisticsManager& StatisticsManager::get() noexcept {
	static StatisticsManager s_Instance;
	return s_Instance;
}