
#include "Game.h"

class TriviaGame : public Game {
private:
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
public:
	TriviaGame(const std::vector<Question>& questions, std::map<LoggedUser, GameData>& players, unsigned int gameID);
	unsigned int getAmountOfPlayers();
	Question getQuestionForUser(LoggedUser user) override;
	void submitAnswer(unsigned int answerId, unsigned int answerTime, LoggedUser player) override;
	void removePlayer(LoggedUser player) override;
	std::vector<PlayerResults> getGameResults(const LoggedUser& loggedUser) override;
};