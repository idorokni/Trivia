#include "Game.h"
#include "Structs.h"

class HeadOnGame : public Game {
private:
	std::pair<std::pair<LoggedUser, HeadOnGameData>, std::pair<LoggedUser, HeadOnGameData>> m_players;
public:
	bool isOpenForPlayer();
};