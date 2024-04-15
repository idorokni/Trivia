#include "RequestHandlerFactory.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() const{
	return new LoginRequestHandler();
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler() const {
	return new MenuRequestHandler();
}

RequestHandlerFactory& RequestHandlerFactory::get() noexcept{
	static RequestHandlerFactory s_Instance;
	return s_Instance;
}