#pragma once
#include <string>

struct ErrorResponse {
	std::string msg;
};

struct LoginResponse {
	unsigned int status;
};

struct SignUpResponse {
	unsigned int status;
};
