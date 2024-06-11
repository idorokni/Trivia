#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(const LoggedUser& loggedUser) {
	m_user = loggedUser.getUsername();
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& info) {
	return info.id == RequestCode::LOGOUT_REQUEST_CODE || info.id == RequestCode::HIGH_SCORE_REQUEST_CODE || info.id == RequestCode::CREATE_ROOM_REQUEST_CODE || info.id == RequestCode::GET_PLAYERS_IN_ROOM_REQUEST_CODE || info.id == RequestCode::GET_ROOMS_REQUEST_CODE || info.id == RequestCode::JOIN_ROOM_REQUEST_CODE || info.id == RequestCode::GET_USER_STATISTICS_REQUEST_CODE;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& info) {
	RequestResult reasult;
	switch (info.id)
	{
	case RequestCode::CREATE_ROOM_REQUEST_CODE:
		reasult = createRoom(info);
		break;
	case RequestCode::GET_PLAYERS_IN_ROOM_REQUEST_CODE:
		reasult = getPlayersInRoom(info);
		break;
	case RequestCode::LOGOUT_REQUEST_CODE:
		reasult = logout(info);
		break;
	case RequestCode::JOIN_ROOM_REQUEST_CODE:
		reasult = joinRoom(info);
		break;
	case RequestCode::HIGH_SCORE_REQUEST_CODE:
		reasult = getHighScore(info);
		break;
	case RequestCode::GET_ROOMS_REQUEST_CODE:
		reasult = getRooms(info);
		break;
	case RequestCode::GET_USER_STATISTICS_REQUEST_CODE:
		reasult = getPersonalStats(info);
		break;
	default:
		break;
	}
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
	reasult.newHandler = this; //should be changed in later versions
	buff = JsonResponsePacketSerializer::serializeResponse(getPlayersInRoomResponse);

	reasult.response = buff;
	return reasult;
}
RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& info) {
	RequestResult reasult;
	Buffer buff;
	GetPersonalStatusResponse getPersonalStatusResponse;
	getPersonalStatusResponse.statistics = StatisticsManager::get().getUserStatistics(m_user.getUsername());
	getPersonalStatusResponse.status = 1;
	reasult.newHandler = this; //should be changed in later versions
	buff = JsonResponsePacketSerializer::serializeResponse(getPersonalStatusResponse);
	reasult.response = buff;
	return reasult;
}
RequestResult MenuRequestHandler::getHighScore(const RequestInfo& info) {
	RequestResult reasult;
	Buffer buff;
	GetHighScoreResponse getHighScoreReponse;
	getHighScoreReponse.statistics = StatisticsManager::get().getHighScore();
	getHighScoreReponse.status = 1;
	reasult.newHandler = this; //should be changed in later versions
	buff = JsonResponsePacketSerializer::serializeResponse(getHighScoreReponse);
	reasult.response = buff;
	return reasult;
}
RequestResult MenuRequestHandler::joinRoom(const RequestInfo& info) {
	RequestResult reasult;
	Buffer buff;
	JoinRoomRequest joinRoomRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buff);
	JoinRoomResponse joinRoomResponse;
	try {
		RoomManager::get().getRoom(joinRoomRequest.roomId).addUser(m_user);
		joinRoomResponse.status = 1;
	}
	catch (...) {
		joinRoomResponse.status = 0;
	}
	reasult.newHandler = this; //should be changed in later versions
	buff = JsonResponsePacketSerializer::serializeResponse(joinRoomResponse);

	reasult.response = buff;
	return reasult;
}
RequestResult MenuRequestHandler::createRoom(const RequestInfo& info) {
	RequestResult reasult;
	Buffer buff;
	CreateRoomRequest createRoomRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.buff);
	CreateRoomResponse createRoomResponse;
	RoomData roomData;
	if (RoomManager::get().getRooms().size() == 0) {
		roomData.id = 0;
	}
	else {
		roomData.id = RoomManager::get().getRooms().end()->id + 1;
	}
	roomData.isActive = true;
	roomData.maxPlayers = createRoomRequest.maxUsers;
	roomData.name = createRoomRequest.roomName;
	roomData.timePerQuestion = createRoomRequest.answerTimeout;
	roomData.numOfQuestionsInGame = createRoomRequest.questionCount;
	try {
		RoomManager::get().createRoom(m_user, roomData);
		createRoomResponse.status = 1;
	}
	catch (...) {
		createRoomResponse.status = 0;
	}
	reasult.newHandler = this; //should be changed in later versions
	buff = JsonResponsePacketSerializer::serializeResponse(createRoomResponse);

	reasult.response = buff;
	return reasult;
}