#pragma once
#include "Structs.h"
#include <string>


enum class ResponseCode {
	ERROR_RESPONSE_CODE = 103,
	LOGIN_RESPONSE_CODE = 101,
	SIGNUP_RESPONSE_CODE = 102,
	LOGOUT_RESPONSE_CODE = 104,
	GET_ROOMS_RESPONSE_CODE = 105,
	GET_PLAYERS_IN_ROOM_RESPONSE = 106,
	GET_HIGH_SCORE_RESPONSE = 107,
	GET_PERSONAL_STATUS_REPONSE = 108,
	JOIN_ROOM_RESPONSE = 109,
	CREATE_ROOM_RESPONSE = 110,
	CLOSE_ROOM_RESPONSE = 111,
	START_GAME_RESPONSE = 112,
	GET_ROOM_STATE_RESPONSE = 113,
	LEAVE_ROOM_RESPONSE = 114,
	GET_GAME_RESULTS_RESPONSE = 115,
	GET_QUESTION_RESPONSE = 116,
	SUBMIT_ANSWER_RESPONSE = 117,
	LEAVE_GAME_RESPONSE = 118
};

struct ErrorResponse {
	std::string msg;
};

struct LoginResponse {
	unsigned int status;
};

struct SignupResponse {
	unsigned int status;
};

struct LogoutResponse {
	unsigned int status;
};

struct GetRoomsResponse {
	unsigned int status;
	std::vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse {
	std::vector<std::string> players;
};

struct GetHighScoreResponse {
	unsigned int status;
	std::vector<std::string> statistics;
};

struct GetPersonalStatusResponse {
	unsigned int status;
	std::vector<std::string> statistics;
};

struct JoinRoomResponse {
	unsigned int status;
};

struct CreateRoomResponse {
	unsigned int status;
};

struct CloseRoomResponse {
	unsigned int status;
};

struct StartGameResponse {
	unsigned int status;
};

struct GetRoomStateResponse {
	unsigned int status;
	RoomState state;
	std::vector<std::string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
};

struct LeaveRoomResponse {
	unsigned int status;
};

struct LeaveGameResponse
{
	unsigned int status;
};

struct GetQuestionResponse
{
	unsigned int status;
	std::string question;
	std::map<unsigned int, std::string> answers;
};

struct SubmitAnswerResponse
{
	unsigned int status;
	unsigned int correctAnswerId;
};

struct GetGameResultsResponse
{
	unsigned int status;
	std::vector<PlayerResults> results;
};

struct PlayerResults
{
	std::string username;
	unsigned int correctAnswerCounter;
	unsigned int wrongAnswerCounter;
	unsigned int averageAnswerTime;
};