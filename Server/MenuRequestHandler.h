#pragma once
#include "IRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "RoomState.h"
#include "RequestHandlerFactory.h"

class MenuRequestHandler : public IRequestHandler {
public:
	MenuRequestHandler(const LoggedUser& loggedUser);
	bool isRequestRelevant(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;
private:
	LoggedUser m_user;

	RequestResult logout(const RequestInfo& info);
	RequestResult getRooms(const RequestInfo& info);
	RequestResult getPlayersInRoom(const RequestInfo& info);
	RequestResult getPersonalStats(const RequestInfo& info);
	RequestResult getHighScore(const RequestInfo& info);
	RequestResult joinRoom(const RequestInfo& info);
	RequestResult createRoom(const RequestInfo& info);
	RequestResult startHeadOnGame(const RequestInfo& info);
};
