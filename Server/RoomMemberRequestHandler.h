#pragma once

#include "IRequestHandler.h"

class RoomMemberRequestHandler : public IRequestHandler {
public:
	bool isRequestRelevant(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;

};
