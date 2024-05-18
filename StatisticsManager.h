#pragma once
#include <string>
#include <vector>

class StatisticsManager {
public:
	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics(const std::string& username);

	static StatisticsManager& get() noexcept;
};
