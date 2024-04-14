#pragma once
#include <string>


enum class ResponseCode {
	ERROR_RESPONSE_CODE = 103,
	LOGIN_RESPONSE_CODE = 101,
	SIGNUP_RESPONSE_CODE = 102
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
