#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse loginResponse) {

	nlohmann::json j;
	j["status"] = loginResponse.status;
	
	std::string jsonDump = j.dump();
	uint32_t dumpLen = jsonDump.length();

	Buffer buff(CODE_AMOUNT_BYTES + BYTES_LENGTH + dumpLen);

	buff.at(0) = LOGIN_RESPONSE_CODE;
	std::memcpy(&buff.data()[CODE_AMOUNT_BYTES], &dumpLen, BYTES_LENGTH);
	std::memcpy(&buff.data()[CODE_AMOUNT_BYTES + BYTES_LENGTH], jsonDump.c_str(), dumpLen);


	return buff;
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse signUpResponse) {
	Buffer buff;
	buff.push_back(SIGNUP_RESPONSE_CODE);

	nlohmann::json j;
	j["status"] = signUpResponse.status;

	std::string jsonDump = j.dump();
	uint32_t dumpLen = jsonDump.length();

	Buffer buff(CODE_AMOUNT_BYTES + BYTES_LENGTH + dumpLen);

	buff.at(0) = LOGIN_RESPONSE_CODE;
	std::memcpy(&buff.data()[CODE_AMOUNT_BYTES], &dumpLen, BYTES_LENGTH);
	std::memcpy(&buff.data()[CODE_AMOUNT_BYTES + BYTES_LENGTH], jsonDump.c_str(), dumpLen);


	return buff;
}

Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse errorResponse) {
	Buffer buff;
	buff.push_back(SIGNUP_RESPONSE_CODE);

	nlohmann::json j;
	j["message"] = errorResponse.msg;

	std::string jsonDump = j.dump();
	uint32_t dumpLen = jsonDump.length();

	Buffer buff(CODE_AMOUNT_BYTES + BYTES_LENGTH + dumpLen);

	buff.at(0) = LOGIN_RESPONSE_CODE;
	std::memcpy(&buff.data()[CODE_AMOUNT_BYTES], &dumpLen, BYTES_LENGTH);
	std::memcpy(&buff.data()[CODE_AMOUNT_BYTES + BYTES_LENGTH], jsonDump.c_str(), dumpLen);


	return buff;
}