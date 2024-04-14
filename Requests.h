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
    SIGNUP_REQUEST_CODE = 52
};

struct LoginRequest {
    std::string username;
    std::string password;
};

struct SignUpRequest {
    std::string username;
    std::string password;
    std::string email;
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
