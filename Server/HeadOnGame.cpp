#include "HeadOnGame.h"

HeadOnGame::HeadOnGame(const LoggedUser& firstPlayer, const LoggedUser& secondPlayer, unsigned int gameID) {
	m_gameId = gameID;
	Question question = IDatabase::get().getQuestions(1).back();
	_firstPlayer = std::make_unique<HeadOnPlayerEntry>(firstPlayer, STARTING_HEALTH, question);
	_secondPlayer = std::make_unique<HeadOnPlayerEntry>(secondPlayer, STARTING_HEALTH, question);
}

bool HeadOnGame::isOpenForPlayer() {
	return _secondPlayer == nullptr;
}

unsigned int HeadOnGame::getPlayerHealth(const LoggedUser& loggedUser) { 
	if (_firstPlayer != nullptr && _firstPlayer->getLoggedUser().getUsername() == loggedUser.getUsername()) {
		return _firstPlayer->getHealth();
	}
	else {
		return _secondPlayer->getHealth();
	}
}

Question HeadOnGame::getQuestionForUser(LoggedUser user) {
	Question question = IDatabase::get().getQuestions(1).back();
	if (_firstPlayer->getLoggedUser().getUsername() == user.getUsername()) {
		_firstPlayer->getLastQuestion() = question;
	}
	else {
		_firstPlayer->getLastQuestion() = question;
	}

	return question;
}
void HeadOnGame::submitAnswer(unsigned int answerId, unsigned int answerTime, LoggedUser player) {
	if (player.getUsername() == _firstPlayer->getLoggedUser().getUsername()) {
		if (_firstPlayer->getLastQuestion().getCorrectAnswerId() == answerId) {
			_secondPlayer->setHealth(_secondPlayer->getHealth() - DEFULT_DAMAGE / answerTime);
		}
	}
	else {
		if (_secondPlayer->getLastQuestion().getCorrectAnswerId() == answerId) {
			_firstPlayer->setHealth(_firstPlayer->getHealth() - DEFULT_DAMAGE / answerTime);
		}
	}
}
void HeadOnGame::removePlayer(LoggedUser player) {
	if (player.getUsername() == _firstPlayer->getLoggedUser().getUsername()) {
		_secondPlayer->setIsWinner();
	}
	else {
		_firstPlayer->setIsWinner();
	}
}

unsigned int HeadOnGame::getAmountOfPlayers() {
	if (_firstPlayer == nullptr && _secondPlayer == nullptr) return 0;
	else if (_firstPlayer != nullptr && _secondPlayer == nullptr || (_firstPlayer == nullptr && _secondPlayer != nullptr)) return 1;
	else return 2;
}