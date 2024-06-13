#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(const LoggedUser& loggedUser, const Room& room) {
    m_room = room;
    m_user = loggedUser;
}

bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo& info) {
	return info.id == RequestCode::LEAVE_ROOM_REQUEST_CODE || info.id == RequestCode::GET_ROOM_STATE_REQUEST_CODE;
}
RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& info) {
    return std::unordered_map<RequestCode, std::function<RequestResult(const RequestInfo&)>>{
        {RequestCode::LEAVE_ROOM_REQUEST_CODE, [this](const RequestInfo& info) { return leaveRoom(info); }},
        { RequestCode::GET_ROOM_STATE_REQUEST_CODE, [this](const RequestInfo& info) { return getRoomState(info); }}
    }.at(info.id)(info);
}
RequestResult RoomMemberRequestHandler::leaveRoom(const RequestInfo& info) {
    RequestResult result;
    Buffer buff;
    LeaveRoomResponse leaveRoomResponse;
    try {
        if (RoomManager::get().isInMap(m_room.getRoomData().id)) {
            RoomManager::get().deleteUserFromGame(m_room.getRoomData().id, m_user);
        }
        leaveRoomResponse.status = 1;
        result.newHandler = RequestHandlerFactory::get().createMenuRequestHandler(m_user);
    }
    catch (...) {
        leaveRoomResponse.status = 0;
        result.newHandler = this;
    }

    result.response = JsonResponsePacketSerializer::serializeResponse(leaveRoomResponse);
    return result;
}
RequestResult RoomMemberRequestHandler::getRoomState(const RequestInfo& info) {
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