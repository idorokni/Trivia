#pragma once
#include <string>

#define ERROR_RESPONSE_CODE 'E'
#define LOGIN_RESPONSE_CODE 'L'
#define SIGNUP_RESPONSE_CODE 'S'

struct ErrorResponse {
	std::string msg;
};

struct LoginResponse {
	unsigned int status;
};

struct SignupResponse {
	unsigned int status;
};
