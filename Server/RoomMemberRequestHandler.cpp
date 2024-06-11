#include "RoomMemberRequestHandler.h"

bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo& info) {
	return info.id == RequestCode::LEAVE_ROOM_REQUEST_CODE || info.id == RequestCode::GET_PLAYERS_IN_ROOM_REQUEST_CODE;
}
RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& info) {

}
RequestResult RoomMemberRequestHandler::leaveRoom(const RequestInfo& info) {

}
RequestResult RoomMemberRequestHandler::getRoomState(const RequestInfo& info) {

}