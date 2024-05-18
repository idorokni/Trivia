#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse loginResponse) {
	nlohmann::json j;
	j["status"] =loginResponse.status;
	Buffer buff = convertToBuffer(j, ResponseCode::LOGIN_RESPONSE_CODE);
	return buff;
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse signUpResponse) {
	nlohmann::json j;
	j["status"] = signUpResponse.status;
	Buffer buff = convertToBuffer(j, ResponseCode::SIGNUP_RESPONSE_CODE);
	return buff;
}

Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse errorResponse) {
	nlohmann::json j;
	j["message"] = errorResponse.msg;
	Buffer buff = convertToBuffer(j, ResponseCode::ERROR_RESPONSE_CODE);
	return buff;
}

Buffer JsonResponsePacketSerializer::serializeResponse(LogoutResponse logoutResponse) {
	nlohmann::json j;
	j["status"] = logoutResponse.status;
	Buffer buff = convertToBuffer(j, ResponseCode::LOGOUT_RESPONSE_CODE);
	return buff;
}
Buffer JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse getRoomsResponseResponse);
Buffer JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse joinRoomResponse);
Buffer JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse createRoomResponseResponse);
Buffer JsonResponsePacketSerializer::serializeResponse(GetHighScoreResponse getHighScoreResponse);
Buffer JsonResponsePacketSerializer::serializeResponse(GetPersonalStatusResponse getPersonalStatusResponse);


Buffer JsonResponsePacketSerializer::convertToBuffer(const nlohmann::json& jsonObj, ResponseCode code) {
	std::string jsonDump = jsonObj.dump();
	uint32_t dumpLen = jsonDump.length();

	Buffer buff(HEADER_LENGTH + dumpLen);

	buff.at(0) = (int)code;
	std::memcpy(&buff.data()[CODE_AMOUNT_BYTES], &dumpLen, BYTES_LENGTH);
	std::memcpy(&buff.data()[HEADER_LENGTH], jsonDump.c_str(), dumpLen);


	return buff;
}
