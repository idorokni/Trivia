#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse loginResponse) {
	Buffer buff;
	buff.bytes.push_back(LOGIN_RESPONSE_CODE);

	nlohmann::json j;
	j["status"] = loginResponse.status;
	
	std::string jsonDump = j.dump();

}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse loginResponse) {

}

Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse loginResponse) {

}