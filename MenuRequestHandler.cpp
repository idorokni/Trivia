#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(const LoggedUser& loggedUser) {
	m_user = loggedUser.getUsername();
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& info) {
	return info.id == (int)RequestCode::LOGOUT_REQUEST_CODE || info.id == (int)RequestCode::CREATE_ROOM_REQUEST_CODE || info.id == (int)RequestCode::GET_PLAYERS_IN_ROOM_REQUEST_CODE || info.id == (int)RequestCode::GET_ROOM_REQUEST_CODE || info.id == (int)RequestCode::JOIN_ROOM_REQUEST_CODE || info.id == (int)RequestCode::GET_USER_STATISTICS_REQUEST_CODE;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& info) {
	RequestResult reasult;
	return reasult;
}

RequestResult MenuRequestHandler::logout(const RequestInfo& info) {
	RequestResult reasult;
	Buffer buff;
	LogoutResponse logoutResponse;
	if (LoginManager::get().logout(m_user.getUsername())) {
		logoutResponse.status = 1;
		reasult.newHandler = this; //should be changed in later versions
	}
	else {
		logoutResponse.status = 0;
		reasult.newHandler = this;
	}
	buff = JsonResponsePacketSerializer::serializeResponse(logoutResponse);

	reasult.response = buff;
	return reasult;
}

RequestResult MenuRequestHandler::getRooms(const RequestInfo& info) {
	RequestResult reasult;
	Buffer buff;
	GetRoomsResponse getRoomsResponse;
	getRoomsResponse.rooms = RoomManager::get().getRooms();
	getRoomsResponse.status = 1;
	buff = JsonResponsePacketSerializer::serializeResponse(getRoomsResponse);
	reasult.newHandler = this; // should change in later versions
	reasult.response = buff;
	return reasult;
}
RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& info) {
	RequestResult reasult;
	Buffer buff;
	GetPlayersInRoomRequest getPlayersInRoomRequest = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(info.buff);
	GetPlayersInRoomResponse getPlayersInRoomResponse;
	getPlayersInRoomResponse.players = RoomManager::get().getRoom(getPlayersInRoomRequest.roomId).getAllUsers();
	reasult.newHandler = this;
	buff = JsonResponsePacketSerializer::serializeResponse(getPlayersInRoomResponse);

	reasult.response = buff;
	return reasult;
}
RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& info) {
	RequestResult reasult;
	Buffer buff;
	GetPersonalStatusResponse getPersonalStatusResponse;
	Statis
	reasult.newHandler = this;
	buff = JsonResponsePacketSerializer::serializeResponse(getPlayersInRoomResponse);

	reasult.response = buff;
	return reasult;
}
RequestResult MenuRequestHandler::getHighScore(const RequestInfo& info);
RequestResult MenuRequestHandler::joinRoom(const RequestInfo& info);
RequestResult MenuRequestHandler::createRoom(const RequestInfo& info);