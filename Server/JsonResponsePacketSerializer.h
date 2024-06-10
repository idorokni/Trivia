#pragma once
#include "Buffer.h"
#include "Responses.h"
#include <iostream>
#include "json.hpp"
#include "Constants.h"

class JsonResponsePacketSerializer {
public:
	//100
	static Buffer serializeResponse(ErrorResponse errorResponse);
	static Buffer serializeResponse(LoginResponse loginResponse);
	static Buffer serializeResponse(SignupResponse signUpResponse);

	//200
	static Buffer serializeResponse(LogoutResponse logoutResponse);
	static Buffer serializeResponse(GetRoomsResponse getRoomsResponse);
	static Buffer serializeResponse(JoinRoomResponse joinRoomResponse);
	static Buffer serializeResponse(CreateRoomResponse createRoomResponse);
	static Buffer serializeResponse(GetHighScoreResponse getHighScoreResponse);
	static Buffer serializeResponse(GetPersonalStatusResponse getPersonalStatusResponse);
	static Buffer serializeResponse(GetPlayersInRoomResponse getPlayersInRoomRespone);

	//300
	static Buffer serializeResponse(CloseRoomResponse closeRoomResponse);
	static Buffer serializeResponse(StartGameResponse startGameResponse);
	static Buffer serializeResponse(GetRoomStateResponse getRoomStateResponse);
	static Buffer serializeResponse(LeaveRoomResponse leaveRoomResponse);

private:
	static Buffer convertToBuffer(const nlohmann::json& jsonObj, ResponseCode code);
};
