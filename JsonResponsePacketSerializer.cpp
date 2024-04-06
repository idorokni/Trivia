#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse loginResponse) {
	Buffer buff;
	buff.bytes.push_back(LOGIN_RESPONSE_CODE);

	nlohmann::json j;
	j["status"] = loginResponse.status;
	
	std::string jsonDump = j.dump();

	buff.bytes.push_back((jsonDump.length() >> FOURTH_BYTE_SHIFT) & ENSURE_LEAST_SIGNIFICANT_BYTE_USE);
	buff.bytes.push_back((jsonDump.length() >> THIRD_BYTE_SHIFT) & ENSURE_LEAST_SIGNIFICANT_BYTE_USE);
	buff.bytes.push_back((jsonDump.length() >> SECEOND_BYTE_SHIFT) & ENSURE_LEAST_SIGNIFICANT_BYTE_USE);
	buff.bytes.push_back(jsonDump.length() & ENSURE_LEAST_SIGNIFICANT_BYTE_USE);

	for (unsigned char ch : jsonDump) {
		buff.bytes.push_back(ch);
	}

	return buff;
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse signUpResponse) {
	Buffer buff;
	buff.bytes.push_back(SIGNUP_RESPONSE_CODE);

	nlohmann::json j;
	j["status"] = signUpResponse.status;

	std::string jsonDump = j.dump();

	buff.bytes.push_back((jsonDump.length() >> FOURTH_BYTE_SHIFT) & ENSURE_LEAST_SIGNIFICANT_BYTE_USE);
	buff.bytes.push_back((jsonDump.length() >> THIRD_BYTE_SHIFT) & ENSURE_LEAST_SIGNIFICANT_BYTE_USE);
	buff.bytes.push_back((jsonDump.length() >> SECEOND_BYTE_SHIFT) & ENSURE_LEAST_SIGNIFICANT_BYTE_USE);
	buff.bytes.push_back(jsonDump.length() & ENSURE_LEAST_SIGNIFICANT_BYTE_USE);

	for (unsigned char ch : jsonDump) {
		buff.bytes.push_back(ch);
	}

	return buff;
}

Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse errorResponse) {
	Buffer buff;
	buff.bytes.push_back(SIGNUP_RESPONSE_CODE);

	nlohmann::json j;
	j["message"] = errorResponse.msg;

	std::string jsonDump = j.dump();

	buff.bytes.push_back((jsonDump.length() >> FOURTH_BYTE_SHIFT) & ENSURE_LEAST_SIGNIFICANT_BYTE_USE);
	buff.bytes.push_back((jsonDump.length() >> THIRD_BYTE_SHIFT) & ENSURE_LEAST_SIGNIFICANT_BYTE_USE);
	buff.bytes.push_back((jsonDump.length() >> SECEOND_BYTE_SHIFT) & ENSURE_LEAST_SIGNIFICANT_BYTE_USE);
	buff.bytes.push_back(jsonDump.length() & ENSURE_LEAST_SIGNIFICANT_BYTE_USE);

	for (unsigned char ch : jsonDump) {
		buff.bytes.push_back(ch);
	}

	return buff;
}