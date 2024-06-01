#pragma once
#include "Structs.h"
#include <string>


enum class ResponseCode {
	ERROR_RESPONSE_CODE = 103,
	LOGIN_RESPONSE_CODE = 101,
	SIGNUP_RESPONSE_CODE = 102,
	LOGOUT_RESPONSE_CODE = 104,
	GET_ROOMS_RESPONSE_CODE = 105,
	GET_PLAYERS_IN_ROOM_RESPONSE = 106,
	GET_HIGH_SCORE_RESPONSE = 107,
	GET_PERSONAL_STATUS_REPONSE = 108,
	JOIN_ROOM_RESPONSE = 109,
	CREATE_ROOM_RESPONSE = 110
};

struct ErrorResponse {
	std::string msg;
};

struct LoginResponse {
	unsigned int status;
};

struct SignupResponse {
	unsigned int status;
};

struct LogoutResponse {
	unsigned int status;
};

struct GetRoomsResponse {
	unsigned int status;
	std::vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse {
	std::vector<std::string> players;
};

struct GetHighScoreResponse {
	unsigned int status;
	std::vector<std::string> statistics;
};

struct GetPersonalStatusResponse {
	unsigned int status;
	std::vector<std::string> statistics;
};

struct JoinRoomResponse {
	unsigned int status;
};

struct CreateRoomResponse {
	unsigned int status;
};