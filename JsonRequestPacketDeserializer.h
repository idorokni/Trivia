#pragma once
#include "Requests.h"
#include "Buffer.h"
#include "Constants.h"
#include "json.hpp"

class JsonRequestPacketDeserializer {
public:
	static LoginRequest deserializeLoginRequest(Buffer buff);
	static SignUpRequest deserializeSignupRequest(Buffer buff);
private:
	static nlohmann::json convertToJsonObject(Buffer buff);
};