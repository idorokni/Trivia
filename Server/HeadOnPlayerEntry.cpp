#include "HeadOnPlayerEntry.h"

HeadOnPlayerEntry::HeadOnPlayerEntry(const LoggedUser& loggedUser, int health, const Question& question)
{
	_loggedUser = loggedUser;
	_health = health;
	_lastQuestion = question;
}

void HeadOnPlayerEntry::setLastQuestion(const Question& question) {
	_lastQuestion = question;
}
void HeadOnPlayerEntry::setIsWinner() {
	_isWinner = 1;
}

const LoggedUser& HeadOnPlayerEntry::getLoggedUser() {
	return _loggedUser;
}

int HeadOnPlayerEntry::getHealth() {
	return _health;
}

Question& HeadOnPlayerEntry::getLastQuestion(){
	return _lastQuestion;
}

unsigned int HeadOnPlayerEntry::getIsWinner() {
	return _isWinner;
}

void HeadOnPlayerEntry::setHealth(int health) {
	_health = health;
}