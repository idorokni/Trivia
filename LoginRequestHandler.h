#pragma once
#include "IRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequestHandlerFactory.h"
#include "LoginManager.h"

class LoginRequestHandler : public IRequestHandler {
public:
	bool isRequestRelevant(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;
private:
	RequestResult login(const RequestInfo& info);
	RequestResult signup(const RequestInfo& info);
};