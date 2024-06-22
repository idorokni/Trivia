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
        if (dynamic_cast<HeadOnGame*>(it->get()) != nullptr) {
            RoomManager::get().deleteRoom(gameId);
        }
    }

}

std::unique_ptr<Game>& GameManager::getOpenGame(const LoggedUser& loggedUser) {
    auto it = std::find_if(m_games.begin(), m_games.end(), [](const std::unique_ptr<Game>& game) { return dynamic_cast<HeadOnGame*>(game.get()) != nullptr && dynamic_cast<HeadOnGame*>(game.get())->isOpenForPlayer(); });
    if (it != m_games.end()) {
        std::unique_ptr<HeadOnPlayerEntry> player = std::make_unique<HeadOnPlayerEntry>(loggedUser, STARTING_HEALTH, dynamic_cast<HeadOnGame*>(it->get())->getFirstPlayersQuestion());
        dynamic_cast<HeadOnGame*>(it->get())->addPlayer(player);
        return *it;
    }
    else {
        std::unique_ptr<HeadOnPlayerEntry> player = std::make_unique<HeadOnPlayerEntry>(loggedUser, STARTING_HEALTH, IDatabase::get().getQuestions(1).back());
        m_games.emplace_back(player, nullptr, RoomManager::get().getLastGivenId());
        RoomManager::get().uploadLastGivenId();
        return m_games.back();
    }
}
Game& GameManager::getGamee(unsigned int roomId) { return **std::find_if(m_games.begin(), m_games.end(), [roomId](const std::unique_ptr<Game>& game) {return game->getGameId() == roomId; }); }

GameManager& GameManager::get() noexcept {
    static GameManager s_Instance;
    return s_Instance;
}