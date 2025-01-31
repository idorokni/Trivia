#include "Question.h"

std::string Question::getQuestion()
{
	return this->m_question;
}

Question::Question()
{
	m_question = "";
}

std::vector<std::string> Question::getPossibleAnswers()
{
	return this->m_possibleAnswers;
}

int Question::getCorrectAnswerId()
{
	return CORRECT_ANSWER_INDEX;
}

Question::Question(const std::string& question, const std::vector<std::string>& answers)
{
	this->m_possibleAnswers = answers;
	this->m_question = question;
}