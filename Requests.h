#pragma once
#include <string>
#include <ctime>
#include <vector>
#include "Buffer.h"
#include "IRequestHandler.h"

class IRequestHandler;

using RequestId = int;

enum class RequestCode {
    LOGIN_REQUEST_CODE = 51,
    SIGNUP_REQUEST_CODE = 52,
    GET_PLAYERS_IN_ROOM_REQUEST_CODE = 53,
    CREATE_ROOM_REQUEST_CODE = 54,
    JOIN_ROOM_REQUEST = 55
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
    RequestId id;
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