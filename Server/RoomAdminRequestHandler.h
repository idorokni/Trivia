#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "LoggedUser.h"
#include "Responses.h"
#include "RoomManager.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"
#include <unordered_map>
#include <functional>

class RoomAdminRequestHandler : public IRequestHandler {
public:
	RoomAdminRequestHandler(const LoggedUser& loggedUser, const Room& room);
	bool isRequestRelevant(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;
private:
	Room m_room;
	LoggedUser m_user;

	RequestResult closeRoom(const RequestInfo& info);
	RequestResult startGame(const RequestInfo& info);
	RequestResult getRoomState(const RequestInfo& info);
};
