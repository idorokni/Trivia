#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "LoggedUser.h"
#include "Requests.h"
#include <unordered_map>
#include <functional>

class RoomMemberRequestHandler : public IRequestHandler {
public:
	bool isRequestRelevant(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;
private:
	Room m_room;
	LoggedUser m_user;

	RequestResult leaveRoom(const RequestInfo& info);
	RequestResult getRoomState(const RequestInfo& info);
};
