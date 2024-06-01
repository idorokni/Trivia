#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& info) {
	return info.id == RequestCode::LOGIN_REQUEST_CODE || info.id == RequestCode::SIGNUP_REQUEST_CODE;
}
RequestResult LoginRequestHandler::handleRequest(const RequestInfo& info) {
	RequestResult reasult;

	try {
		if (info.id == RequestCode::LOGIN_REQUEST_CODE) {
			reasult = login(info);
		}
		else {
			reasult = signup(info);
		}
	}
	catch (const std::exception& e) {
		Buffer buff;
		reasult.newHandler = nullptr;
		ErrorResponse errResponse;
		errResponse.msg = "cant process request";
		buff = JsonResponsePacketSerializer::serializeResponse(errResponse);
		reasult.response = buff;

	}

	return reasult;
}

RequestResult LoginRequestHandler::login(const RequestInfo& info) {
	RequestResult reasult;
	Buffer buff;
	LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buff);
	LoginResponse loginResponse;
	if (LoginManager::get().login(loginRequest.password, loginRequest.username)) {
		loginResponse.status = 1;
		reasult.newHandler = RequestHandlerFactory::get().createMenuRequestHandler(LoggedUser(loginRequest.username));
	}
	else {
		loginResponse.status = 0;
		reasult.newHandler = this;
	}
	buff = JsonResponsePacketSerializer::serializeResponse(loginResponse);

	reasult.response = buff;
	return reasult;
}
RequestResult LoginRequestHandler::signup(const RequestInfo& info) {
	RequestResult reasult;
	Buffer buff;
	SignUpRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buff);
	SignupResponse signupResponse;
	if (LoginManager::get().signup(signupRequest.password, signupRequest.username, signupRequest.email, signupRequest.address, signupRequest.phone, signupRequest.birthday)) {
		signupResponse.status = 1;
		reasult.newHandler = RequestHandlerFactory::get().createMenuRequestHandler(LoggedUser(signupRequest.username));
	}
	else {
		signupResponse.status = 0;
		reasult.newHandler = this;
	}
	buff = JsonResponsePacketSerializer::serializeResponse(signupResponse);

	reasult.response = buff;
	return reasult;
}