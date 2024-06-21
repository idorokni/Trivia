#pragma once
#include "IDatabase.h"
#include "TriviaGame.h"
#include "Room.h"
#include "HeadOnGame.h"

class GameManager
{
private:
	//IDatabase* m_database;
	std::vector<std::unique_ptr<Game>> m_games;
	//unsigned int lastGivenId = 0;

public:
	Game& createGame(Room room);
	void deleteGame(unsigned int gameId);
	Game& getGamee(unsigned int roomId);
	std::unique_ptr<Game>& getOpenGame();
	static GameManager& get() noexcept;

};