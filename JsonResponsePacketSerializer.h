#pragma once
#include "Buffer.h"
#include "Responses.h"
#include <iostream>
#include "json.hpp"
#include "Constants.h"

class JsonResponsePacketSerializer {
public:
	static Buffer serializeResponse(ErrorResponse errorResponse);
	static Buffer serializeResponse(LoginResponse loginResponse);
	static Buffer serializeResponse(SignupResponse signUpResponse);
	static Buffer serializeResponse(LogoutResponse logoutResponse);
	static Buffer serializeResponse(GetRoomsResponse getRoomsResponseResponse);
	static Buffer serializeResponse(JoinRoomResponse joinRoomResponse);
	static Buffer serializeResponse(CreateRoomResponse createRoomResponseResponse);
	static Buffer serializeResponse(GetHighScoreResponse getHighScoreResponse);
	static Buffer serializeResponse(GetPersonalStatusResponse getPersonalStatusResponse);
private:
	static Buffer convertToBuffer(const nlohmann::json& jsonObj, ResponseCode code);
};
