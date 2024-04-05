#pragma once
#include "Buffer.h"
#include "Responses.h"
#include <iostream>
#include "json.hpp"

class JsonResponsePacketSerializer {
public:
	static Buffer serializeResponse(ErrorResponse errorResponse);
	static Buffer serializeResponse(LoginResponse loginResponse);
	static Buffer serializeResponse(SignupResponse signUpResponse);
};
