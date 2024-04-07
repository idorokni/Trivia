#pragma once
#include <string>
#include <ctime>
#include <vector>

enum class RequestCode {
	LOGIN_REQUEST_CODE = 51,
	SIGNUP_REQUEST_CODE = 52
};

struct RequestId {
	int id;
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

struct RequestInfo {
	RequestId id;
	std::time_t recivalTime;
	std::vector<unsigned char> buffer;
};