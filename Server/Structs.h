#pragma once
#include <string>
#include "RoomState.h"
#include "Question.h"

struct RoomData {
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	RoomState isActive;
};

struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
	unsigned int lastGivenQuestionId;
	bool isFinished = false;

	//GameData(Question CurrentQuestion, unsigned int CorrectAnswerCount, unsigned int WrongAnswerCount, unsigned int AverageAnswerTime) : currentQuestion(CurrentQuestion), correctAnswerCount(CorrectAnswerCount), wrongAnswerCount(WrongAnswerCount), averageAnswerTime(AverageAnswerTime) {}
};

struct PlayerResults
{
	std::string username;
	unsigned int correctAnswerCounter;
	unsigned int wrongAnswerCounter;
	unsigned int averageAnswerTime;
};