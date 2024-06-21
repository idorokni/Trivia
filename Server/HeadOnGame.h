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
public:
	bool isOpenForPlayer();
	unsigned int getPlayerHealth(const LoggedUser& loggedUser);
	HeadOnGame(const LoggedUser& firstPlayer, const LoggedUser& secondPlayer, unsigned int gameID);
	Question getQuestionForUser(LoggedUser user) override;
	void submitAnswer(unsigned int answerId, unsigned int answerTime, LoggedUser player) override;
	void removePlayer(LoggedUser player) override;
};