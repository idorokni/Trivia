#include "StatisticsManager.h"

std::vector<std::string> StatisticsManager::getHighScore() {
	std::vector<std::string> vec;
	return vec;
}

std::vector<std::string> StatisticsManager::getUserStatistics(const std::string& userame) {
	std::vector<std::string> vec;
	return vec;
}

StatisticsManager& StatisticsManager::get() noexcept {
	static StatisticsManager s_Instance;
	return s_Instance;
}