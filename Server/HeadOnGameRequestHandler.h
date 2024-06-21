#include "GameRequestHandler.h"

class HeadOnGameRequestHandler : public GameRequestHandler {
public:
	HeadOnGameRequestHandler(Game& game, const LoggedUser& loggedUser);
	RequestResult getHeadOnGameHealthState(const RequestInfo& info);
};