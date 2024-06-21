#include "GameManager.h"

Game& GameManager::createGame(Room room)
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
        gameData.lastGivenQuestionId = 0;
        players[loggedUser] = gameData;
    }

    m_games.emplace_back(std::make_unique<TriviaGame>(questionsVector, players, room.getRoomData().id));
    std::cout << "adding room, rooms = " << m_games.size() << std::endl;
    return *m_games.back();
}

void GameManager::deleteGame(unsigned int gameId)
{
    auto it = std::find_if(m_games.begin(), m_games.end(), [gameId](const std::unique_ptr<Game>& game) {return game->getGameId() == gameId; });
    if (it != m_games.end()) {
        m_games.erase(it);
    }

}

//std::unique_ptr<Game> GameManager::getOpenGame() { return std::find_if(m_games.begin(), m_games.end(), [](const std::unique_ptr<Game>& game) {}); }

Game& GameManager::getGamee(unsigned int roomId) { return **std::find_if(m_games.begin(), m_games.end(), [roomId](const std::unique_ptr<Game>& game) {return game->getGameId() == roomId; }); }

GameManager& GameManager::get() noexcept {
    static GameManager s_Instance;
    return s_Instance;
}