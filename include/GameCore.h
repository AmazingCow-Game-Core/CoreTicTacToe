#pragma once

//std
#include <string>
#include <utility>
#include <vector>
//AmazingCow Libs
#include "CoreGame.h"
#include "CoreRandom.h"
//CoreTicTacToe
#include "CoreTicTacToe_Utils.h"
#include "CoreTicTacToe_Types.h"
#include "Board.h"

NS_CORETTT_BEGIN

class GameCore
{
    // CTOR / DTOR //
public:
    GameCore(
        Player     starter,
        GameMode   mode,
        AIStrength aiStrength,
        int        seed = CoreRandom::Random::kRandomSeed
    );

    // Public Methods //
public:
    //Actions
    bool makeMove(int positionIndex);

    //Game State
    CoreGame::Status getStatus() const;

    Player getCurrentPlayer() const;
    Player getWinnerPlayer () const;

    //Getters
    const Board& getBoard() const;
    GameMode getGameMode() const;

    //AI
    AIStrength getAIStrength() const;
    int        getAIMove    () const;

    //Seed
    int  getSeed          () const;
    bool isUsingRandomSeed() const;

    //Ascii
    std::string ascii() const;


    // Private Methods //
private:
    //Helpers
    Player getNextPlayer(Player player) const;

    //AI
    int findBestMove(Board board) const;

    // iVars //
private:
    Board              m_board;
    Player             m_currPlayer;
    GameMode           m_mode;
    AIStrength         m_aiStrength;
    CoreRandom::Random m_random;
};

NS_CORETTT_END
