#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(Game& game, const LoggedUser& loggedUser) : BasicGameRequestHandler(game, loggedUser) {}

bool GameRequestHandler::isRequestRelevant(const RequestInfo& info)
{
	return BasicGameRequestHandler::isRequestRelevant(info) || info.id == RequestCode::GET_GAME_RESULT_REQUEST_CODE;
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& info) {
    if (info.id == RequestCode::GET_GAME_RESULT_REQUEST_CODE) {
        return getGameResult(info);
    }
    else {
        return BasicGameRequestHandler::handleRequest(info);
    }
}


RequestResult GameRequestHandler::getGameResult(const RequestInfo& info)
{
    RequestResult result;
    Buffer buff;
    GetGameResultsResponse getGameResultsResponse;

    try {
        getGameResultsResponse.results = m_game.getGameResults(m_user);
        getGameResultsResponse.status = 1;
        result.newHandler = this; // I thing shouldnt be changed - needed to ask rokni
    }
    catch (...) {
        getGameResultsResponse.status = 0;
        result.newHandler = this;
    }

    result.response = JsonResponsePacketSerializer::serializeResponse(getGameResultsResponse);
    return result;
}