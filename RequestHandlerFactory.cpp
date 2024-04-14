#include "RequestHandlerFactory.h"

RequestHandlerFactory RequestHandlerFactory::s_Instance;

const LoginManager& RequestHandlerFactory::getLoginManager() const noexcept{
	return m_loginManager;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() const{
	return new LoginRequestHandler();
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler() const {
	return new MenuRequestHandler();
}

RequestHandlerFactory& RequestHandlerFactory::getFactory() {
	return s_Instance;
}