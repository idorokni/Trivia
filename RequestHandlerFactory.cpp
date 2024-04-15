#include "RequestHandlerFactory.h"

RequestHandlerFactory RequestHandlerFactory::s_Instance;


LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() const{
	return new LoginRequestHandler();
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler() const {
	return new MenuRequestHandler();
}

RequestHandlerFactory& RequestHandlerFactory::get() noexcept{
	return s_Instance;
}