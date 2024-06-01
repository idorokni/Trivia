#pragma once
#include "LoginManager.h"
#include "IDatabase.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory {
public:
	LoginRequestHandler* createLoginRequestHandler() const;
	MenuRequestHandler* createMenuRequestHandler(const LoggedUser& loggedUser) const;

	static RequestHandlerFactory& get() noexcept;
};
