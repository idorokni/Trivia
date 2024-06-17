#pragma once
#include "LoginManager.h"
#include "IDatabase.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;

class RequestHandlerFactory {
public:
	LoginRequestHandler* createLoginRequestHandler() const;
	MenuRequestHandler* createMenuRequestHandler(const LoggedUser& loggedUser) const;
	RoomAdminRequestHandler* createRoomAdminRequestHandler(const LoggedUser& loggedUser, const Room& room);
	RoomMemberRequestHandler* creatRoomMemberRequestHandler(const LoggedUser& loggedUser, const Room& room);
	GameRequestHandler* createGameRequestHandler(Game& game, const LoggedUser& loggedUser);


	static RequestHandlerFactory& get() noexcept;
};
