#pragma once
#include <string>
#include <ctime>
#include <vector>
#include "Buffer.h"
#include "IRequestHandler.h"

class IRequestHandler;

enum class RequestCode{
    LOGIN_REQUEST_CODE = 51,
    SIGNUP_REQUEST_CODE = 52,
    GET_PLAYERS_IN_ROOM_REQUEST_CODE = 53,
    CREATE_ROOM_REQUEST_CODE = 54,
    JOIN_ROOM_REQUEST_CODE = 55,
    HIGH_SCORE_REQUEST_CODE = 56,
    LOGOUT_REQUEST_CODE = 57,
    GET_ROOMS_REQUEST_CODE = 58,
    GET_USER_STATISTICS_REQUEST_CODE = 59
};

struct LoginRequest {
    std::string username;
    std::string password;
};

struct SignUpRequest {
    std::string username;
    std::string password;
    std::string email;
    std::string address;
    std::string phone;
    std::string birthday;
};

struct RequestResult {
    Buffer response;
    IRequestHandler* newHandler;
};

struct RequestInfo {
    RequestCode id;
    std::time_t recivalTime;
    Buffer buff;
};

struct GetPlayersInRoomRequest {
    unsigned int roomId;
};

struct JoinRoomRequest {
    unsigned int roomId;
};

struct CreateRoomRequest {
    std::string roomName;
    unsigned int maxUsers;
    unsigned int questionCount;
    unsigned int answerTimeout;
};