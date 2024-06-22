#pragma once
#include "Game.h"
#include "Structs.h"
#include "HeadOnPlayerEntry.h"
#include "Constants.h"
#include <optional>
class HeadOnGame : public Game {
private:
	std::unique_ptr<HeadOnPlayerEntry> _firstPlayer;
	std::unique_ptr<HeadOnPlayerEntry> _secondPlayer;
	unsigned int _firstPlayerAmountOfQuestions;
	unsigned int _secondPlayerAmountOfQuestions;
public:
	bool isOpenForPlayer();
	unsigned int getPlayerHealth(const LoggedUser& loggedUser);
	void addPlayer(std::unique_ptr<HeadOnPlayerEntry>& player);
	HeadOnGame(std::unique_ptr<HeadOnPlayerEntry>& firstPlayer, std::unique_ptr<HeadOnPlayerEntry>& secondPlayer, unsigned int gameID);
	Question& getFirstPlayersQuestion();
	Question getQuestionForUser(LoggedUser user) override;
	void submitAnswer(unsigned int answerId, unsigned int answerTime, LoggedUser player) override;
	void removePlayer(LoggedUser player) override;
	unsigned int getAmountOfPlayers() override;
};