#include "HeadOnGame.h"

HeadOnGame::HeadOnGame(std::unique_ptr<HeadOnPlayerEntry>& firstPlayer, std::unique_ptr<HeadOnPlayerEntry>& secondPlayer, unsigned int gameID) {
	m_gameId = gameID;
	Question question = IDatabase::get().getQuestions(1).back();
	_firstPlayer = std::move(firstPlayer);
	_secondPlayer = std::move(secondPlayer);
	_firstPlayerAmountOfQuestions = 1;
	_secondPlayerAmountOfQuestions = 1;
}

bool HeadOnGame::isOpenForPlayer() {
	return _secondPlayer == nullptr;
}

void HeadOnGame::addPlayer(std::unique_ptr<HeadOnPlayerEntry>& player) {
	_secondPlayer = std::move(player);
}

Question& HeadOnGame::getFirstPlayersQuestion() {
	return _firstPlayer->getLastQuestion();
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
	Question question;
	if (_firstPlayer->getLoggedUser().getUsername() == user.getUsername()) {
		question = IDatabase::get().getQuestions(_firstPlayerAmountOfQuestions).back();
		_firstPlayer->getLastQuestion() = question;
		_firstPlayerAmountOfQuestions++;
	}
	else {
		question = IDatabase::get().getQuestions(_secondPlayerAmountOfQuestions).back();
		_firstPlayer->getLastQuestion() = question;
		_secondPlayerAmountOfQuestions++;
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