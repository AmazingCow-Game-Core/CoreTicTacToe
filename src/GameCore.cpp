//Header
#include "../include/GameCore.h"
//std
#include <algorithm>
#include <iostream>
    using namespace std;
//Usings
USING_NS_CORETTT;


Player c2p(std::string c)
{
    if(c == "x")
        return Player::X;
    if(c == "o")
        return Player::O;

    return Player::None;
}

void startBoard(Board &board,
    std::string p0, std::string p1, std::string p2,
    std::string p3, std::string p4, std::string p5,
    std::string p6, std::string p7, std::string p8)
{
    board.putPlayerAt(0, c2p(p0));
    board.putPlayerAt(1, c2p(p1));
    board.putPlayerAt(2, c2p(p2));
    board.putPlayerAt(3, c2p(p3));
    board.putPlayerAt(4, c2p(p4));
    board.putPlayerAt(5, c2p(p5));
    board.putPlayerAt(6, c2p(p6));
    board.putPlayerAt(7, c2p(p7));
    board.putPlayerAt(8, c2p(p8));
}

////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
GameCore::GameCore(
    Player     starter,
    GameMode   mode,
    AIStrength aiStrength,
    int        seed /* = CoreRandom::Random::kRandomSeed */) :
    // m_board      - Default initialized.
    m_currPlayer(starter   ),
    m_mode      (mode      ),
    m_aiStrength(aiStrength),
    m_random    (seed      )
{
    //Random starter.
    if(starter == Player::None)
    {
        m_currPlayer = (m_random.nextBool())
                        ? Player::X
                        : Player::O;
    }

    //AI cannot be None in Multiplayer
    //  so we set to Medium strength.
    if(m_mode == GameMode::Multi && m_aiStrength == AIStrength::None)
        m_aiStrength = AIStrength::Medium;
    //AI is meaningless in Single player
    else
        m_aiStrength = AIStrength::None;


//    startBoard(m_board,
//        " ", " ", "o",
//        "o", "o", "x",
//        "x", "o", "x"
//    );
}



////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
//Actions
bool GameCore::makeMove(int positionIndex)
{
    //Already has a player there.
    if(m_board.getPlayerAt(positionIndex) != Player::None)
        return false;

    m_board.putPlayerAt(positionIndex, m_currPlayer);

    //Turn the player.
    m_currPlayer = (m_currPlayer == Player::X)
                    ? Player::O
                    : Player::X;

    return true;
}

//Game State
CoreGame::Status GameCore::getStatus() const
{
    if(m_board.getWinner() == Player::None && m_board.hasPossibleMoves())
        return CoreGame::Status::Continue;

    return CoreGame::Status::Victory;
}

Player GameCore::getCurrentPlayer() const
{
    return m_currPlayer;
}

Player GameCore::getWinnerPlayer() const
{
    return m_board.getWinner();
}


//Getters
const Board& GameCore::getBoard() const
{
    return m_board;
}

GameMode GameCore::getGameMode() const
{
    return m_mode;
}


//AI
AIStrength GameCore::getAIStrength() const
{
    return m_aiStrength;
}

int GameCore::getAIMove() const
{
    COREGAME_ASSERT(
        (m_mode == GameMode::Single),
        "GameCore is not in GameMode::Multi"
    );

    return findBestMove(m_board);
}


//Seed
int GameCore::getSeed() const
{
    return m_random.getSeed();
}

bool GameCore::isUsingRandomSeed() const
{
    return m_random.isUsingRandomSeed();
}


//Ascii
std::string GameCore::ascii() const
{
    return m_board.ascii();
}


////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
//Helpers
Player GameCore::getNextPlayer(Player player) const
{
    return (player == Player::O) ? Player::X : Player::O;
}


//AI
int GameCore::findBestMove(Board board) const
{
    for(int i = 0; i < 9; ++i)
        if(board.getPlayerAt(i) == Player::None)
            return i;

    return -1;
}
