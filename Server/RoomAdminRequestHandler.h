#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "LoggedUser.h"

class RoomAdminRequestHandler : public IRequestHandler {
public:
	bool isRequestRelevant(const RequestInfo& info);
	RequestResult handleRequest(const RequestInfo& info);
private:
	Room m_room;
	LoggedUser m_user;

	RequestResult closeRoom(const RequestInfo& info);
	RequestResult startGame(const RequestInfo& info);
	RequestResult getRoomState(const RequestInfo& info);
};
