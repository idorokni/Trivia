#include "JsonResponsePacketSerializer.h"
#include "RoomManager.h"

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse loginResponse) {
	nlohmann::json j;
	j["status"] =loginResponse.status;
	j["error"] = loginResponse.errorMsg;
	return convertToBuffer(j, ResponseCode::LOGIN_RESPONSE_CODE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse signUpResponse) {
	nlohmann::json j;
	j["status"] = signUpResponse.status;
	j["error"] = signUpResponse.errorMsg;
	return convertToBuffer(j, ResponseCode::SIGNUP_RESPONSE_CODE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse errorResponse) {
	nlohmann::json j;
	j["message"] = errorResponse.msg;
	return convertToBuffer(j, ResponseCode::ERROR_RESPONSE_CODE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(LogoutResponse logoutResponse) {
	nlohmann::json j;
	j["status"] = logoutResponse.status;
	return convertToBuffer(j, ResponseCode::LOGOUT_RESPONSE_CODE);
}
Buffer JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse getRoomsResponse) {
	nlohmann::json j;
	std::string roomsString = "";
	// j structure:
	// {"Rooms":"userlist-""user1," "user2"..., roomdata-...; again, ... }
	for (RoomData data : getRoomsResponse.rooms) 
	{ 
		roomsString += "userlist-";
		for (std::string user : RoomManager::get().getRoom(data.id).getAllUsers()) {
			roomsString += user + ",";
		}
		roomsString += "roomdata-";
		roomsString += data.name + ","; 
		roomsString += std::to_string(data.maxPlayers) + ",";
		roomsString += std::to_string(data.numOfQuestionsInGame) + ",";
		roomsString += std::to_string(data.timePerQuestion) + ",";
		roomsString += std::to_string(data.id) + ";";
	}
	roomsString.erase(roomsString.end());
	j["Rooms"] = roomsString;
	j["status"] = getRoomsResponse.status;
	return convertToBuffer(j, ResponseCode::GET_ROOMS_RESPONSE_CODE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse joinRoomResponse) {
	nlohmann::json j;
	j["status"] = joinRoomResponse.status;
	return convertToBuffer(j, ResponseCode::JOIN_ROOM_RESPONSE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse createRoomResponse, unsigned int id) {
	nlohmann::json j;
	j["status"] = createRoomResponse.status;
	j["id"] = id;
	return convertToBuffer(j, ResponseCode::CREATE_ROOM_RESPONSE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetHighScoreResponse getHighScoreResponse) {
	nlohmann::json j;
	std::string statisticsString = "";
	for (std::string data : getHighScoreResponse.statistics) { statisticsString += data + ","; }
	statisticsString.erase(statisticsString.end());
	j["status"] = getHighScoreResponse.status;
	j["highScores"] = statisticsString;
	return convertToBuffer(j, ResponseCode::GET_HIGH_SCORE_RESPONSE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetPersonalStatusResponse getPersonalStatusResponse) {
	nlohmann::json j;
	std::string statisticsString = "";
	for (std::string data : getPersonalStatusResponse.statistics) { statisticsString += data + ","; }
	statisticsString.erase(statisticsString.end());
	j["status"] = getPersonalStatusResponse.status;
	j["userStats"] = statisticsString;
	return convertToBuffer(j, ResponseCode::GET_PERSONAL_STATUS_REPONSE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse getPlayersInRoomResponse){
	nlohmann::json j;
	std::string playersString = "";
	for (std::string data : getPlayersInRoomResponse.players) { playersString += data + ","; }
	playersString.erase(playersString.end());
	j["players"] = playersString;
	return convertToBuffer(j, ResponseCode::GET_PERSONAL_STATUS_REPONSE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse closeRoomResponse)
{
	nlohmann::json j;
	j["status"] = closeRoomResponse.status;
	return convertToBuffer(j, ResponseCode::CLOSE_ROOM_RESPONSE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(StartGameResponse startGameResponse)
{
	nlohmann::json j;
	j["status"] = startGameResponse.status;
	return convertToBuffer(j, ResponseCode::START_GAME_RESPONSE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse getRoomStateResponse)
{
	nlohmann::json j;
	j["status"] = getRoomStateResponse.status;
	j["hasGameBegun"] = (int)getRoomStateResponse.state;
	std::string playersString = "";
	for (std::string data : getRoomStateResponse.players) { playersString += data + ","; }
	playersString.erase(playersString.end());
	j["players"] = playersString;	
	j["questionCount"] = getRoomStateResponse.questionCount;
	j["answerTimeout"] = getRoomStateResponse.answerTimeout;
	return convertToBuffer(j, ResponseCode::GET_ROOM_STATE_RESPONSE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse leaveRoomResponse)
{
	nlohmann::json j;
	j["status"] = leaveRoomResponse.status;
	return convertToBuffer(j, ResponseCode::LEAVE_ROOM_RESPONSE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetGameResultsResponse getGameResultsResponse)
{
	nlohmann::json j;
	j["status"] = getGameResultsResponse.status;
	std::string resultsString = "";
	if (getGameResultsResponse.status == 1)
	{
		for (PlayerResults playerResults : getGameResultsResponse.results)
		{
			resultsString += playerResults.username + "," + std::to_string(playerResults.correctAnswerCounter) + "," + std::to_string(playerResults.wrongAnswerCounter) + "," + std::to_string(playerResults.averageAnswerTime) + "-";
		}
		resultsString.erase(resultsString.end() - 1);
		j["results"] = resultsString;
	}
	j["results"] = resultsString;
	return convertToBuffer(j, ResponseCode::GET_GAME_RESULTS_RESPONSE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(SubmitAnswerResponse submitAnswerResponse)
{
	nlohmann::json j;
	j["status"] = submitAnswerResponse.status;
	j["correctId"] = submitAnswerResponse.correctAnswerId;
	return convertToBuffer(j, ResponseCode::SUBMIT_ANSWER_RESPONSE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetQuestionResponse getQuestionResponse)
{
	nlohmann::json j;
	j["status"] = getQuestionResponse.status;
	j["question"] = getQuestionResponse.question;
	std::string answersString = "";
	if (getQuestionResponse.status == 1)
	{
		for (std::pair<unsigned int, std::string> pair : getQuestionResponse.answers)
		{
			answersString += std::to_string(pair.first) + "-" + pair.second + ",";
		}
		answersString.erase(answersString.end());
	}
	j["answers"] = answersString;
	return convertToBuffer(j, ResponseCode::GET_QUESTION_RESPONSE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(LeaveGameResponse leaveGameResponse)
{
	nlohmann::json j;
	j["status"] = leaveGameResponse.status;
	return convertToBuffer(j, ResponseCode::LEAVE_GAME_RESPONSE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetHeadOnGameStateResponse getHeadOnGameStateResponse)
{
	nlohmann::json j;
	j["status"] = getHeadOnGameStateResponse.status;
	j["health"] = getHeadOnGameStateResponse.health;
	j["isWinner"] = getHeadOnGameStateResponse.isWinner;
	return convertToBuffer(j, ResponseCode::GET_HEAD_ON_GAME_STATE_RESPONSE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(StartHeadOnGameResponse startHeadOnGameResponse)
{
	nlohmann::json j;
	j["status"] = startHeadOnGameResponse.status;
	return convertToBuffer(j, ResponseCode::START_HEAD_ON_GAME_RESPONSE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(AddQuestionResponse addQuestionResponse)
{
	nlohmann::json j;
	j["status"] = addQuestionResponse.status;
	return convertToBuffer(j, ResponseCode::ADD_QUESTION_RESPONSE);
}


Buffer JsonResponsePacketSerializer::convertToBuffer(const nlohmann::json& jsonObj, ResponseCode code) {
	std::string jsonDump = jsonObj.dump();
	uint32_t dumpLen = jsonDump.length();

	Buffer buff(HEADER_LENGTH + dumpLen);

	buff.at(0) = (int)code;
	std::memcpy(&buff.data()[CODE_AMOUNT_BYTES], &dumpLen, BYTES_LENGTH);
	std::memcpy(&buff.data()[HEADER_LENGTH], jsonDump.c_str(), dumpLen);


	return buff;
}
