#pragma once
#include "LoginManager.h"
#include "IDatabase.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"

class RequestHandlerFactory {
private:
	LoginManager m_loginManager;
	IDatabase* m_database;
public:
	const LoginManager& getLoginManager() const noexcept;
	LoginRequestHandler* createLoginRequestHandler() const;
	MenuRequestHandler* createMenuRequestHandler() const;
};
