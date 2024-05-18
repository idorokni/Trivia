#include "MenuRequestHandler.h"

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& info) {
	return info.id == (int)RequestCode::LOGOUT_REQUEST_CODE || info.id == (int)RequestCode::CREATE_ROOM_REQUEST_CODE || info.id == (int)RequestCode::GET_PLAYERS_IN_ROOM_REQUEST_CODE || info.id == (int)RequestCode::GET_ROOM_REQUEST_CODE || info.id == (int)RequestCode::JOIN_ROOM_REQUEST_CODE || info.id == (int)RequestCode::GET_USER_STATISTICS_REQUEST_CODE;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& info) {
	RequestResult reasult;
	return reasult;
}