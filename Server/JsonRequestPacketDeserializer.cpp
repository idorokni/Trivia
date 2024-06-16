#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
#include <iostream>

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(Buffer buff) {
	LoginRequest loginRequest;
	nlohmann::json jsonObj = convertToJsonObject(buff);
	if(jsonObj.contains("password") && jsonObj.contains("username")) {
		loginRequest.username = std::move(jsonObj["username"]);
		loginRequest.password = std::move(jsonObj["password"]);
	}



	return loginRequest;

}
SignUpRequest JsonRequestPacketDeserializer::deserializeSignupRequest(Buffer buff) {
	SignUpRequest signupRequest;
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

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(Buffer buff) {
	GetPlayersInRoomRequest getPlayersInRoomRequest;
	nlohmann::json jsonObj = convertToJsonObject(buff);
	if (jsonObj.contains("roomId")) {
		getPlayersInRoomRequest.roomId = jsonObj["roomId"];
	}

	return getPlayersInRoomRequest;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(Buffer buff) {
	JoinRoomRequest joinRoomRequest;
	nlohmann::json jsonObj = convertToJsonObject(buff);
	if (jsonObj.contains("roomId")) {
		joinRoomRequest.roomId = jsonObj["roomId"];
	}

	return joinRoomRequest;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(Buffer buff) {
	CreateRoomRequest createRoomRequest;
	nlohmann::json jsonObj = convertToJsonObject(buff);
	if (jsonObj.contains("roomName") && jsonObj.contains("maxUsers") && jsonObj.contains("questionCount") && jsonObj.contains("answerTimeout")) {
		createRoomRequest.roomName = std::move(jsonObj["roomName"]);
		createRoomRequest.maxUsers = jsonObj["maxUsers"];
		createRoomRequest.questionCount = jsonObj["questionCount"];
		createRoomRequest.answerTimeout = jsonObj["answerTimeout"];
	}

	return createRoomRequest;
}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(Buffer buff)
{
	SubmitAnswerRequest submitAnswerRequest;
	nlohmann::json jsonObj = convertToJsonObject(buff);
	if (jsonObj.contains("_answerId")) submitAnswerRequest.answerId = jsonObj["_answerId"];
	return submitAnswerRequest;
}

nlohmann::json JsonRequestPacketDeserializer::convertToJsonObject(Buffer buff) {
	uint32_t length;
	std::memcpy(&length, &buff.data()[CODE_AMOUNT_BYTES], BYTES_LENGTH);

	return nlohmann::json::parse(std::string((char*)&buff.at(HEADER_LENGTH), length));
}
