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
		loginRequest.username = std::move(jsonObj["username"]);
		loginRequest.password = std::move(jsonObj["password"]);
	}



	return loginRequest;

}
SignUpRequest JsonRequestPacketDeserializer::deserializeSignupRequest(Buffer buff) {
	SignUpRequest signupRequest;
	if ((int)buff.at(0) != (int)RequestCode::SIGNUP_REQUEST_CODE) {
		throw std::exception("not proper code");
	}
	nlohmann::json jsonObj = convertToJsonObject(buff);
	if (jsonObj.contains("password") && jsonObj.contains("username") && jsonObj.contains("mail") && jsonObj.contains("address") && jsonObj.contains("phone") && jsonObj.contains("birthday")) 
	{
		signupRequest.username = std::move(jsonObj["username"]);
		signupRequest.password = std::move(jsonObj["password"]);
		signupRequest.email = std::move(jsonObj["mail"]);
		signupRequest.address = std::move(jsonObj["address"]);
		signupRequest.phone = std::move(jsonObj["phone"]);
		signupRequest.birthday = std::move(jsonObj["birthday"]);
	}
	return signupRequest;
}

nlohmann::json JsonRequestPacketDeserializer::convertToJsonObject(Buffer buff) {
	uint32_t length;
	std::memcpy(&length, &buff.data()[CODE_AMOUNT_BYTES], BYTES_LENGTH);

	return nlohmann::json::parse(std::string((char*)&buff.at(HEADER_LENGTH), length));
}
