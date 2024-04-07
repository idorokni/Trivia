#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
#include <iostream>

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(Buffer buff) {
	LoginRequest loginRequest;
	std::cout << (int)RequestCode::LOGIN_REQUEST_CODE << std::endl;
	if ((int)buff.at(0) != (int)RequestCode::LOGIN_REQUEST_CODE) {
		throw std::exception("not proper code");
	}
	nlohmann::json jsonObj = convertToJsonObject(buff);
	if(jsonObj.contains("password") && jsonObj.contains("username")) {
		loginRequest.username = jsonObj["username"];
		loginRequest.password = jsonObj["password"];
	}



	return loginRequest;

}
SignUpRequest JsonRequestPacketDeserializer::deserializeSignupRequest(Buffer buff) {
	SignUpRequest signupRequest;
	if ((int)buff.at(0) != (int)RequestCode::SIGNUP_REQUEST_CODE) {
		throw std::exception("not proper code");
	}
	nlohmann::json jsonObj = convertToJsonObject(buff);
	if (jsonObj.contains("password") && jsonObj.contains("username")) {
		signupRequest.username = jsonObj["username"];
		signupRequest.password = jsonObj["password"];
	}
	return signupRequest;
}

nlohmann::json JsonRequestPacketDeserializer::convertToJsonObject(Buffer buff) {
	uint32_t length;
	std::memcpy(&length, &buff.data()[CODE_AMOUNT_BYTES], BYTES_LENGTH);
	nlohmann::json jsonObj = std::string(buff.begin() + HEADER_LENGTH, buff.begin() + HEADER_LENGTH + length);

	return jsonObj;
}
