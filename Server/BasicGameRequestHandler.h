#pragma once
#include "IRequestHandler.h"
#include "Game.h"
#include "LoggedUser.h"
#include "GameManager.h"
#include "Responses.h"
#include "RoomManager.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include <unordered_map>
#include <functional>

class BasicGameRequestHandler : public IRequestHandler{
public:
	bool isRequestRelevant(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;
	BasicGameRequestHandler(Game& game, const LoggedUser& loggedUser);

protected:
	Game& m_game;
	LoggedUser m_user;

private:
	RequestResult getQuestion(const RequestInfo& info);
	RequestResult submitAnswer(const RequestInfo& info);
	RequestResult leaveGame(const RequestInfo& info);
};