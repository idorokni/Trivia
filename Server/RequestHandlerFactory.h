#pragma once
#include "LoginManager.h"
#include "IDatabase.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory {
public:
	LoginRequestHandler* createLoginRequestHandler() const;
	MenuRequestHandler* createMenuRequestHandler(const LoggedUser& loggedUser) const;
	RoomAdminRequestHandler* createRoomAdminRequestHandler(const LoggedUser& loggedUser, const Room& room);

	static RequestHandlerFactory& get() noexcept;
};
