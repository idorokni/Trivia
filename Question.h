#pragma once
#include <iostream>
#include <vector>
#define CORRECT_ANSWER_INDEX 1;

class Question
{
public:
	std::string getQuestion();
	std::vector<std::string> getPossibleAnswers();
	int getCorrectAnswerId();

private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
};