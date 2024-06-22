#pragma once
#include "Requests.h"
#include "Buffer.h"
#include "Constants.h"
#include "json.hpp"

class JsonRequestPacketDeserializer {
public:
	static LoginRequest deserializeLoginRequest(Buffer buff);
	static SignUpRequest deserializeSignupRequest(Buffer buff);
	static GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(Buffer buff);
	static JoinRoomRequest deserializeJoinRoomRequest(Buffer buff);
	static CreateRoomRequest deserializeCreateRoomRequest(Buffer buff);
	static SubmitAnswerRequest deserializeSubmitAnswerRequest(Buffer buff);
	static AddQuestionRequest deserializeAddQuestionRequest(Buffer buff);
private:
	static nlohmann::json convertToJsonObject(Buffer buff);
};