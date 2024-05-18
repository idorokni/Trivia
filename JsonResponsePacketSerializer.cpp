#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse loginResponse) {
	nlohmann::json j;
	j["status"] =loginResponse.status;

	std::string jsonDump = j.dump();
	uint32_t dumpLen = jsonDump.length();

	Buffer buff(HEADER_LENGTH + dumpLen);

	buff.at(0) = (int)ResponseCode::LOGIN_RESPONSE_CODE;
	std::memcpy(&buff.data()[CODE_AMOUNT_BYTES], &dumpLen, BYTES_LENGTH);
	std::memcpy(&buff.data()[HEADER_LENGTH], jsonDump.c_str(), dumpLen);


	return buff;
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse signUpResponse) {
	nlohmann::json j;
	j["status"] = signUpResponse.status;

	std::string jsonDump = j.dump();
	uint32_t dumpLen = jsonDump.length();

	Buffer buff(HEADER_LENGTH + dumpLen);

	buff.at(0) = (int)ResponseCode::SIGNUP_RESPONSE_CODE;
	std::memcpy(&buff.data()[CODE_AMOUNT_BYTES], &dumpLen, BYTES_LENGTH);
	std::memcpy(&buff.data()[HEADER_LENGTH], jsonDump.c_str(), dumpLen);


	return buff;
}

Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse errorResponse) {
	nlohmann::json j;
	j["message"] = errorResponse.msg;

	std::string jsonDump = j.dump();
	uint32_t dumpLen = jsonDump.length();

	Buffer buff(HEADER_LENGTH + dumpLen);

	buff.at(0) = (int)ResponseCode::ERROR_RESPONSE_CODE;
	std::memcpy(&buff.data()[CODE_AMOUNT_BYTES], &dumpLen, BYTES_LENGTH);
	std::memcpy(&buff.data()[HEADER_LENGTH], jsonDump.c_str(), dumpLen);


	return buff;
}

Buffer JsonResponsePacketSerializer::serializeResponse(LogoutResponse logoutResponse);
Buffer JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse getRoomsResponseResponse);
Buffer JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse joinRoomResponse);
Buffer JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse createRoomResponseResponse);
Buffer JsonResponsePacketSerializer::serializeResponse(GetHighScoreResponse getHighScoreResponse);
Buffer JsonResponsePacketSerializer::serializeResponse(GetPersonalStatusResponse getPersonalStatusResponse);