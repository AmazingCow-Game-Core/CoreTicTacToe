#pragma once

//std
#include <string>
#include <vector>
//AmazingCow Libs
#include "CoreGame.h"
#include "CoreRandom.h"
//CoreTicTacToe
#include "CoreTicTacToe_Utils.h"
#include "CoreTicTacToe_Types.h"


NS_CORETTT_BEGIN

class Board
{
    // CTOR / DTOR //
public:
    Board();


    // Public Methods //
public:
    void   putPlayerAt(int pos, Player player);
    Player getPlayerAt(int pos) const;

    Player getWinner() const;

    bool hasPossibleMoves() const;

    std::string ascii() const;

    // Private Methods //
public:
    void checkVictory();
    bool checkVictoryHelper(int initialPos, int increment);


    // iVars //
private:
    Player m_winner;
    int    m_movesCount;

    std::vector<std::vector<Player>> m_board;
};

NS_CORETTT_END
