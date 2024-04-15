#pragma once
#include "LoginManager.h"
#include "IDatabase.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory {
private:
	IDatabase* m_database = nullptr;

	static RequestHandlerFactory s_Instance;
public:
	LoginRequestHandler* createLoginRequestHandler() const;
	MenuRequestHandler* createMenuRequestHandler() const;

	static RequestHandlerFactory& get() noexcept;
};
