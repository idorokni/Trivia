#pragma once
#include "BasicGameRequestHandler.h"
#include "HeadOnGame.h"

class HeadOnGameRequestHandler : public BasicGameRequestHandler {
public:
	HeadOnGameRequestHandler(Game& game, const LoggedUser& loggedUser);
	bool isRequestRelevant(const RequestInfo& info);
	RequestResult handleRequest(const RequestInfo& info);
private:
	RequestResult getHeadOnGameState(const RequestInfo& info);
};