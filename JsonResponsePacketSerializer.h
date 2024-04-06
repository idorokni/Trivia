#pragma once
#include "Buffer.h"
#include "Responses.h"
#include <iostream>
#include "json.hpp"

#define FOURTH_BYTE_SHIFT 24
#define THIRD_BYTE_SHIFT 16
#define SECEOND_BYTE_SHIFT 8
#define ENSURE_LEAST_SIGNIFICANT_BYTE_USE 0xFF

class JsonResponsePacketSerializer {
public:
	static Buffer serializeResponse(ErrorResponse errorResponse);
	static Buffer serializeResponse(LoginResponse loginResponse);
	static Buffer serializeResponse(SignupResponse signUpResponse);
};
