#pragma once
#include "BasicGameRequestHandler.h"

class GameRequestHandler : public BasicGameRequestHandler
{
public:
	bool isRequestRelevant(const RequestInfo& info);
	RequestResult handleRequest(const RequestInfo& info);
	GameRequestHandler(Game& game, const LoggedUser& loggedUser);

private:
	RequestResult getGameResult(const RequestInfo& info);

};