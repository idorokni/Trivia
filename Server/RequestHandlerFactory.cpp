#include "RequestHandlerFactory.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() const {
	return new LoginRequestHandler();
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(const LoggedUser& loggedUser) const {
	return new MenuRequestHandler(loggedUser);
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(const LoggedUser& loggedUser, const Room& room) {
	return new RoomAdminRequestHandler(loggedUser, room);
}

RoomMemberRequestHandler* RequestHandlerFactory::creatRoomMemberRequestHandler(const LoggedUser& loggedUser, const Room& room) {
	return new RoomMemberRequestHandler(loggedUser, room);
}

BasicGameRequestHandler* RequestHandlerFactory::createGameRequestHandler(Game& game, const LoggedUser& loggedUser)
{
	return new GameRequestHandler(game, loggedUser);
}

BasicGameRequestHandler* RequestHandlerFactory::createHeadOnGameRequestHandler(Game& game, const LoggedUser& loggedUser) {
	return new HeadOnGameRequestHandler(game, loggedUser);
}

RequestHandlerFactory& RequestHandlerFactory::get() noexcept{
	static RequestHandlerFactory s_Instance;
	return s_Instance;
}