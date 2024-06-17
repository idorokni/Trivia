#pragma once
#include "Buffer.h"
#include "Responses.h"
#include <iostream>
#include "json.hpp"
#include "Constants.h"
#include "Structs.h"

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
	static Buffer serializeResponse(CreateRoomResponse createRoomResponse, unsigned int id);
	static Buffer serializeResponse(GetHighScoreResponse getHighScoreResponse);
	static Buffer serializeResponse(GetPersonalStatusResponse getPersonalStatusResponse);
	static Buffer serializeResponse(GetPlayersInRoomResponse getPlayersInRoomRespone);

	//300
	static Buffer serializeResponse(CloseRoomResponse closeRoomResponse);
	static Buffer serializeResponse(StartGameResponse startGameResponse);
	static Buffer serializeResponse(GetRoomStateResponse getRoomStateResponse);
	static Buffer serializeResponse(LeaveRoomResponse leaveRoomResponse);

	//400
	static Buffer serializeResponse(GetGameResultsResponse getGameResultsResponse);
	static Buffer serializeResponse(SubmitAnswerResponse submitAnswerResponse);
	static Buffer serializeResponse(GetQuestionResponse getQuestionResponse);
	static Buffer serializeResponse(LeaveGameResponse leaveGameResponse);


private:
	static Buffer convertToBuffer(const nlohmann::json& jsonObj, ResponseCode code);
};
