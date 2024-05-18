#include "RequestHandlerFactory.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() const{
	return new LoginRequestHandler();
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(const LoggedUser& loggedUser) const {
	return new MenuRequestHandler(loggedUser);
}

RequestHandlerFactory& RequestHandlerFactory::get() noexcept{
	static RequestHandlerFactory s_Instance;
	return s_Instance;
}