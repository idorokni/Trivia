#include "RoomMemberRequestHandler.h"

bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo& info) {
	return info.id == RequestCode::LEAVE_ROOM_REQUEST_CODE || info.id == RequestCode::GET_PLAYERS_IN_ROOM_REQUEST_CODE;
}
RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& info) {
    return std::unordered_map<RequestCode, std::function<RequestResult(const RequestInfo&)>>{
        {RequestCode::LEAVE_ROOM_REQUEST_CODE, [this](const RequestInfo& info) { return leaveRoom(info); }},
        { RequestCode::GET_ROOM_STATE_REQUEST_CODE, [this](const RequestInfo& info) { return getRoomState(info); }}
    }.at(info.id)(info);
}
RequestResult RoomMemberRequestHandler::leaveRoom(const RequestInfo& info) {

}
RequestResult RoomMemberRequestHandler::getRoomState(const RequestInfo& info) {

}