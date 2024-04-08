#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& info) {
	return info.id == (int)RequestCode::LOGIN_REQUEST_CODE || info.id == (int)RequestCode::SIGNUP_REQUEST_CODE;
}
RequestResult LoginRequestHandler::handleRequest(const RequestInfo& info) {
	Buffer buff;
	if (info.id == (int)RequestCode::LOGIN_REQUEST_CODE) {
		LoginRequest login = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buff);
		LoginResponse loginResponse;
		loginResponse.status = 1; //should be checked with data base later
		buff = JsonResponsePacketSerializer::serializeResponse(loginResponse);
	}
	else {

		SignUpRequest signUp = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buff);
		SignupResponse signupResponse;
		signupResponse.status = 1; //should be checked with data base later
		buff = JsonResponsePacketSerializer::serializeResponse(signupResponse);

	}
	
	RequestResult reasult;
	reasult.newHandler = this; //should be changed according to states in later virsions
	reasult.response = buff;
	return reasult;
}