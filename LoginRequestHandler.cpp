#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& info) {
	return info.id == (int)RequestCode::LOGIN_REQUEST_CODE || info.id == (int)RequestCode::SIGNUP_REQUEST_CODE;
}
RequestResult LoginRequestHandler::handleRequest(const RequestInfo& info) {
	RequestResult reasult;
	
	return reasult;
}