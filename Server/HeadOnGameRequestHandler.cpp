#include "HeadOnGameRequestHandler.h"

HeadOnGameRequestHandler::HeadOnGameRequestHandler(Game& game, const LoggedUser& loggedUser) : GameRequestHandler(game, loggedUser) {

}

RequestResult HeadOnGameRequestHandler::getHeadOnGameHealthState(const RequestInfo& info) {
    RequestResult result;
    Buffer buff;
    GetHeadOnGameState leavGameResponse;
    int i = 0;

    try {
        m_game.removePlayer(m_user);
        if (dynamic_cast<TriviaGame&>(m_game).getAmountOfPlayers() == 0) {
            GameManager::get().deleteGame(m_game.getGameId());
            RoomManager::get().deleteRoom(m_game.getGameId());
        }
        //RoomManager::get().deleteUserFromGame(RoomManager::get().);
        leaveGameResponse.status = 1;
        result.newHandler = RequestHandlerFactory::get().createMenuRequestHandler(m_user);
    }
    catch (...) {
        leaveGameResponse.status = 0;
        result.newHandler = this;
    }

    result.response = JsonResponsePacketSerializer::serializeResponse(leaveGameResponse);
    return result;
}