#include "RequestHandlerFactory.h"

const LoginManager& RequestHandlerFactory::getLoginManager() const noexcept{
	return m_loginManager;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() const{
	return new LoginRequestHandler();
}