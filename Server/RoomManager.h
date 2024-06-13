#pragma once
#include <unordered_map>
#include "Room.h"
#include "Responses.h"
#include <vector>

using roomID = int;

class RoomManager {
private:
	std::unordered_map<roomID, Room> m_rooms;
	int lastGivenId = 0;

public:
	void createRoom(const LoggedUser& loggedUser, const RoomData& roomData);
	void deleteRoom(int ID);
	void startGame(int ID);
	void deleteUserFromGame(int ID, const LoggedUser& loggedUser);
	void getRoomState(GetRoomStateResponse& getRoomStateResponse, int ID);
	const std::vector<RoomData> getRooms() const;
	Room& getRoom(int ID);
	int getLastGivenId();
	void uploadLastGivenId();

	static RoomManager& get() noexcept;
};
