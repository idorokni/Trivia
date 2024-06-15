#pragma once
#include "IRequestHandler.h"
#include "Game.h"
#include "LoggedUser.h"
#include "GameManager.h"
#include "RequestHandlerFactory.h"


class GameRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;
	GameRequestHandler(Game& game, const LoggedUser& loggedUser);

private:
	Game& m_game;
	LoggedUser m_user;

	RequestResult getQuestion(const RequestInfo& info);	
	RequestResult submitAnswer(const RequestInfo& info);
	RequestResult getGameResult(const RequestInfo& info);
	RequestResult leaveGame(const RequestInfo& info);

};