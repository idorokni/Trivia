#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(const LoggedUser& loggedUser, const Room& room) {
    m_user = loggedUser;
    m_room = room;
}

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& info) {
	return info.id == RequestCode::CLOSE_ROOM_REQUEST_CODE || info.id == RequestCode::GET_ROOM_STATE_REQUEST_CODE || info.id == RequestCode::START_GAME_REQUEST_CODE;
}
RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& info) {
    return std::unordered_map<RequestCode, std::function<RequestResult(const RequestInfo&)>>{
        {RequestCode::CLOSE_ROOM_REQUEST_CODE, [this](const RequestInfo& info) { return closeRoom(info); }},
        { RequestCode::START_GAME_REQUEST_CODE, [this](const RequestInfo& info) { return startGame(info); }},
        { RequestCode::GET_ROOM_STATE_REQUEST_CODE, [this](const RequestInfo& info) { return getRoomState(info); } }
    }.at(info.id)(info);
}

RequestResult RoomAdminRequestHandler::closeRoom(const RequestInfo& info) {
    RequestResult result;
    Buffer buff;
    CloseRoomResponse closeRoomResponse;
    try {
        RoomManager::get().deleteRoom(m_room.getRoomData().id);
        closeRoomResponse.status = 1;
        result.newHandler = RequestHandlerFactory::get().createMenuRequestHandler(m_user);
    }
    catch (...) {
        closeRoomResponse.status = 0;
        result.newHandler = this;
    }
    result.response = JsonResponsePacketSerializer::serializeResponse(closeRoomResponse);
    return result;

    
}
RequestResult RoomAdminRequestHandler::startGame(const RequestInfo& info) {
    RequestResult result;
    Buffer buff;
    StartGameResponse startGameResponse;
    try {
        RoomManager::get().startGame(m_room.getRoomData().id);
        startGameResponse.status = 1;
        Game game = GameManager::get().createGame(m_room);
        result.newHandler = RequestHandlerFactory::get().createGameRequestHandler(game, m_user); //was changed in 400
    }
    catch (...) {
        startGameResponse.status = 0;
        result.newHandler = this;
    }

    result.response = JsonResponsePacketSerializer::serializeResponse(startGameResponse);
    return result;
}

RequestResult RoomAdminRequestHandler::getRoomState(const RequestInfo& info) {
    RequestResult result;
    Buffer buff;
    GetRoomStateResponse getRoomStateResponse;
    try {
        RoomManager::get().getRoomState(getRoomStateResponse, m_room.getRoomData().id);
        getRoomStateResponse.status = 1;
        result.newHandler = this;
    }
    catch (...) {
        getRoomStateResponse.status = 0;
        result.newHandler = this;
    }

    result.response = JsonResponsePacketSerializer::serializeResponse(getRoomStateResponse);
    return result;
}