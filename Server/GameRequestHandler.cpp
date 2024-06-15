#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(Game& game, const LoggedUser& loggedUser) : m_game(game), m_user(loggedUser) {}

bool GameRequestHandler::isRequestRelevant(const RequestInfo& info)
{
	return info.id == RequestCode::LEAVE_GAME_REQUEST_CODE || info.id == RequestCode::GET_QUESTION_REQUEST_CODE || info.id == RequestCode::SUBMIT_ANSWER_REUEST_CODE || info.id == RequestCode::GET_GAME_RESULT_REQUEST_CODE;
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& info) {
    return std::unordered_map<RequestCode, std::function<RequestResult(const RequestInfo&)>>{
        {RequestCode::LEAVE_GAME_REQUEST_CODE, [this](const RequestInfo& info) { return leaveGame(info); } },
        { RequestCode::GET_QUESTION_REQUEST_CODE, [this](const RequestInfo& info) { return getQuestion(info); } },
        { RequestCode::SUBMIT_ANSWER_REUEST_CODE, [this](const RequestInfo& info) { return submitAnswer(info); } },
        { RequestCode::GET_GAME_RESULT_REQUEST_CODE, [this](const RequestInfo& info) { return getGameResult(info); } }
    }.at(info.id)(info);
}

RequestResult GameRequestHandler::getQuestion(const RequestInfo& info)
{
	RequestResult result;
	Buffer buff;
	GetQuestionResponse getQuestionResponse;
    int i = 0;

    try {
        Question question = m_game.getQuestionForUser(m_user);
        getQuestionResponse.question = question.getQuestion();
        for (std::string answer : question.getPossibleAnswers())
        {
            getQuestionResponse.answers[i] = answer;
            i++;
        }
        getQuestionResponse.status = 1;
        result.newHandler = this; // I thing shouldnt be changed - needed to ask rokni
    }
    catch (...) {
        getQuestionResponse.status = 0;
        result.newHandler = this;
    }

    result.response = JsonResponsePacketSerializer::serializeResponse(getQuestionResponse);
    return result;
}

RequestResult GameRequestHandler::submitAnswer(const RequestInfo& info)
{
    RequestResult result;
    Buffer buff;
    SubmitAnswerRequest submitAnswerRequest = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(info.buff);
    SubmitAnswerResponse submitAnswerResponse;

    try {
        m_game.submitAnswer(submitAnswerRequest.answerId, m_user);
        submitAnswerResponse.correctAnswerId = submitAnswerRequest.answerId;
        submitAnswerResponse.status = 1;
        result.newHandler = this; // I thing shouldnt be changed - needed to ask rokni
    }
    catch (...) {
        submitAnswerResponse.status = 0;
        result.newHandler = this;
    }

    result.response = JsonResponsePacketSerializer::serializeResponse(submitAnswerResponse);
    return result;
}

RequestResult GameRequestHandler::getGameResult(const RequestInfo& info)
{
    RequestResult result;
    Buffer buff;
    GetGameResultsResponse getGameResultsResponse;

    try {
        getGameResultsResponse.results = m_game.getGameResults();
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

RequestResult GameRequestHandler::leaveGame(const RequestInfo& info)
{
    RequestResult result;
    Buffer buff;
    LeaveGameResponse leaveGameResponse;
    int i = 0;

    try {
        m_game.removePlayer(m_user);
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