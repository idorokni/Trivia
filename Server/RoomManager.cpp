#include "RoomManager.h"

void RoomManager::createRoom(const LoggedUser& loggedUser, const RoomData& roomData) {
	m_rooms.emplace(roomData.id, Room(loggedUser, roomData));
}
void RoomManager::deleteRoom(int ID) {
	m_rooms.erase(ID);
}
void RoomManager::getRoomState(GetRoomStateResponse& getRoomStateResponse, int ID) {
	try {
		Room room = m_rooms.at(ID);
		getRoomStateResponse.questionCount = room.getRoomData().numOfQuestionsInGame;
		getRoomStateResponse.answerTimeout = room.getRoomData().timePerQuestion;
		getRoomStateResponse.players = room.getAllUsers();
		getRoomStateResponse.state = room.getRoomData().isActive;
	}
	catch (...) {
		getRoomStateResponse.state = RoomState::ROOM_CLOSED;
	}
}
const std::vector<RoomData> RoomManager::getRooms() const {
	std::vector<RoomData> data;
	for (auto& room : m_rooms) {
		data.push_back(room.second.getRoomData());
	}

	return data;
}

void RoomManager::startGame(int ID) {
	m_rooms.at(ID).getRoomData().isActive = RoomState::GAME_STARTED;
}
Room& RoomManager::getRoom(int ID) {
	return m_rooms.at(ID);
}

void RoomManager::deleteUserFromGame(int ID, const LoggedUser& loggedUser) {
	m_rooms.at(ID).removeUser(loggedUser);
}

int RoomManager::getLastGivenId()
{
	return lastGivenId;
}

void RoomManager::uploadLastGivenId()
{
	lastGivenId = lastGivenId + 1;
}

bool RoomManager::isInMap(int id) noexcept { return m_rooms.find(id) != m_rooms.end(); }

RoomManager& RoomManager::get() noexcept {
	static RoomManager s_Instance;
	return s_Instance;
}