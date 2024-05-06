#include "RoomManager.h"

void RoomManager::createRoom(const LoggedUser& loggedUser, const RoomData& roomData) {
	m_rooms.at(roomData.id) = Room(loggedUser, roomData);

}
void RoomManager::deleteRoom(int ID) {
	m_rooms.erase(ID);
}
unsigned int RoomManager::getRoomState(int ID) {
	return 1;
}
const std::vector<RoomData> RoomManager::getRooms() const {
	std::vector<RoomData> data;
	for (const auto& room : m_rooms) {
		data.push_back(room.second.getRoomData());
	}

	return data;
}
const Room& RoomManager::getRoom(int ID) const {
	return m_rooms.at(ID);
}
