#include "RoomManager.h"

void RoomManager::createRoom(const LoggedUser& loggedUser, const RoomData& roomData) {
	m_rooms.emplace(roomData.id, Room(loggedUser, roomData));
}
void RoomManager::deleteRoom(int ID) {
	m_rooms.erase(ID);
}
unsigned int RoomManager::getRoomState(int ID) {
	return 1;
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

RoomManager& RoomManager::get() noexcept {
	static RoomManager s_Instance;
	return s_Instance;
}