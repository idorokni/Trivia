#pragma once
#include "GameRequestHandler.h"
#include "HeadOnGame.h"

class HeadOnGameRequestHandler : public GameRequestHandler {
public:
	bool isRequestRelevant(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;

	HeadOnGameRequestHandler(Game& game, const LoggedUser& loggedUser);
	RequestResult getHeadOnGameState(const RequestInfo& info);
};