#include "HeadOnGameRequestHandler.h"
#include "RequestHandlerFactory.h"

HeadOnGameRequestHandler::HeadOnGameRequestHandler(Game& game, const LoggedUser& loggedUser) : BasicGameRequestHandler(game, loggedUser) {

}

bool HeadOnGameRequestHandler::isRequestRelevant(const RequestInfo& info) {
    return info.id == RequestCode::GET_HEAD_ON_GAME_STATE_REQUEST_CODE || BasicGameRequestHandler::isRequestRelevant(info);
}
RequestResult HeadOnGameRequestHandler::handleRequest(const RequestInfo& info) {
    if (info.id == RequestCode::GET_HEAD_ON_GAME_STATE_REQUEST_CODE) {
        return getHeadOnGameState(info);
    }
    else {
        return BasicGameRequestHandler::handleRequest(info);
    }
}

RequestResult HeadOnGameRequestHandler::getHeadOnGameState(const RequestInfo& info) {
    RequestResult result;
    Buffer buff;
    GetHeadOnGameStateResponse getHeadOnGameStateResponse;
    int i = 0;

    try {
        getHeadOnGameStateResponse.isWinner = 0;
        result.newHandler = this;
        if (dynamic_cast<HeadOnGame&>(m_game).isOpenForPlayer()) {
            getHeadOnGameStateResponse.health = 0;
            getHeadOnGameStateResponse.status = 2;
        }
        else {
            getHeadOnGameStateResponse.health = dynamic_cast<HeadOnGame&>(m_game).getPlayerHealth(m_user);
            if (getHeadOnGameStateResponse.health <= 0) {
                result.newHandler = RequestHandlerFactory::get().createMenuRequestHandler(m_user);
                dynamic_cast<HeadOnGame&>(m_game).setOtherPlayerToWinner(m_user);
                getHeadOnGameStateResponse.isWinner = dynamic_cast<HeadOnGame&>(m_game).winningState(m_user);
            }
            getHeadOnGameStateResponse.status = 1;
        }
    }
    catch (...) {
        getHeadOnGameStateResponse.status = 0;
        result.newHandler = this;
    }

    result.response = JsonResponsePacketSerializer::serializeResponse(getHeadOnGameStateResponse);
    return result;
}