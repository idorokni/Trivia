#include "GameManager.h"

Game GameManager::createGame(Room room)
{
    std::list<Question> questionsList = IDatabase::get().getQuestions(room.getRoomData().numOfQuestionsInGame);
    std::vector<Question> questionsVector;
    questionsVector.reserve(questionsList.size());
    for (const auto& question : questionsList) questionsVector.push_back(question);
    
    std::map<LoggedUser, GameData> players;
    for (LoggedUser loggedUser : room.getAllUsers())
    {
        GameData gameData;
        gameData.currentQuestion = questionsVector[0];
        gameData.correctAnswerCount = 0;
        gameData.wrongAnswerCount = 0;
        gameData.averageAnswerTime = 0;
        players[loggedUser] = gameData;
    }

    m_games.emplace_back(questionsVector, players, room.getRoomData().id);
    return Game(questionsVector, players, room.getRoomData().id);
}

void GameManager::deleteGame(unsigned int gameId)
{
    auto it = m_games.begin();
    for (Game game : m_games)
    {
        if (game.getGameId() == gameId)
        {
            m_games.erase(it);
            break;
        }
        else it++;
    }
}

GameManager& GameManager::get() noexcept {
    static GameManager s_Instance;
    return s_Instance;
}