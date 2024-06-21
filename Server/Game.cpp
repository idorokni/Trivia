#include "Game.h"

void Game::submitGameStatsToDB(const GameData& gameData, const LoggedUser& player)
{
	IDatabase::get().submitGameStatistics(gameData, player);
}
