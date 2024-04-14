#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& info) {
	return info.id == (int)RequestCode::LOGIN_REQUEST_CODE || info.id == (int)RequestCode::SIGNUP_REQUEST_CODE;
}
RequestResult LoginRequestHandler::handleRequest(const RequestInfo& info) {
	Buffer buff;
	RequestResult reasult;

	try {
		if (info.id == (int)RequestCode::LOGIN_REQUEST_CODE) {
			LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buff);
			LoginResponse loginResponse;
			if (LoginManager::get().login(loginRequest.password, loginRequest.username)) {
				loginResponse.status = 1;
				reasult.newHandler = RequestHandlerFactory::get().createMenuRequestHandler();
			}
			else {
				loginResponse.status = 0;
			}
			buff = JsonResponsePacketSerializer::serializeResponse(loginResponse);
		}
		else {

			SignUpRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buff);
			SignupResponse signupResponse;
			if (LoginManager::get().signup(signupRequest.password, signupRequest.username, signupRequest.email)) {
				signupResponse.status = 1;
				reasult.newHandler = RequestHandlerFactory::get().createMenuRequestHandler();
			}
			else {
				signupResponse.status = 0;
			}
			buff = JsonResponsePacketSerializer::serializeResponse(signupResponse);

		}
	}
	catch (const std::exception& e) {
		reasult.newHandler = nullptr;
		ErrorResponse errResponse;
		errResponse.msg = e.what();
		buff = JsonResponsePacketSerializer::serializeResponse(errResponse);

	}
	
	reasult.response = buff;
	return reasult;
}