#pragma once
#include "IRequestHandler.h"
#include "Game.h"
#include "LoggedUser.h"

class BasicGameRequestHandler : public IRequestHandler{
public:
	bool isRequestRelevant(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;
	BasicGameRequestHandler(Game& game, const LoggedUser& loggedUser);

protected:
	Game& m_game;
	LoggedUser m_user;

	RequestResult getQuestion(const RequestInfo& info);
	RequestResult submitAnswer(const RequestInfo& info);
	RequestResult getGameResult(const RequestInfo& info);
	RequestResult leaveGame(const RequestInfo& info);
};