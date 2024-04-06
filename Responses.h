#pragma once
#include <string>

#define ERROR_RESPONSE_CODE 103
#define LOGIN_RESPONSE_CODE 101
#define SIGNUP_RESPONSE_CODE 102

struct ErrorResponse {
	std::string msg;
};

struct LoginResponse {
	unsigned int status;
};

struct SignupResponse {
	unsigned int status;
};
