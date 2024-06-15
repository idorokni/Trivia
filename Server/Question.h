#pragma once
#include <iostream>
#include <vector>
#include <string>
#define CORRECT_ANSWER_INDEX 1

class Question
{
public:
	Question(const std::string& question, const std::vector<std::string>& answers);
	std::string getQuestion();
	std::vector<std::string> getPossibleAnswers();
	int getCorrectAnswerId();
	Question();
private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
};