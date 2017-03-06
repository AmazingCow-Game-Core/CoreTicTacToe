//Header
#include "../include/Board.h"
//std
#include <sstream>

//Usings
USING_NS_CORETTT;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Board::Board() :
    m_winner    (Player::None),
    m_movesCount(0)
{
    //Init board.
    m_board.reserve(3);
    for(int i = 0; i < 3; ++i)
    {
        m_board.push_back(std::vector<Player>());

        m_board[i].reserve(3);
        for(int j = 0; j < 3; ++j)
            m_board[i].push_back(Player::None);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
void Board::putPlayerAt(int pos, Player player)
{
    COREGAME_ASSERT_ARGS(
        (pos >= 0 && pos < 9),
        "pos(%d) is invalid! Range:[0..9)",
        pos
    );

    int y = pos / 3;
    int x = pos % 3;

    m_board[y][x] = player;

    if(player != Player::None)
        ++m_movesCount;

    checkVictory();
}

Player Board::getPlayerAt(int pos) const
{
    COREGAME_ASSERT_ARGS(
        (pos >= 0 && pos < 9),
        "pos(%d) is invalid! Range:[0..9)",
        pos
    );

    int y = pos / 3;
    int x = pos % 3;

    return m_board[y][x];
}

Player Board::getWinner() const
{
    return m_winner;
}

bool Board::hasPossibleMoves() const
{
    for(int i = 0; i < 9; ++i)
        if(getPlayerAt(i) == Player::None)
            return true;

    return false;
}

std::string Board::ascii() const
{
    int index = 0;

    std::stringstream ss;
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            auto player = getPlayerAt(index);

            if     (player == Player::None) ss << ". ";
            else if(player == Player::X ) ss << "X ";
            else if(player == Player::O ) ss << "O ";

            ++index;
        }
        ss << std::endl;
    }

    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
void Board::checkVictory()
{
    //There's no point to search a winner
    //when we already have one.
    if(m_winner != Player::None)
        return;

    // How we are checking for the winner?
    // We can notice that the board is formed
    // by a 3x3 "matrix", so we must check the
    // index:
    //   0, 1, 2 -> Horizontal Line 1
    //   3, 4, 5 -> Horizontal Line 2
    //   6, 7, 8 -> Horizontal Line 3
    //
    //   0, 3, 6 -> Vertical Line 1
    //   1, 4, 7 -> Vertical Line 2
    //   2, 5, 8 -> Vertical Line 3
    //
    //   0, 4, 8 -> Diagonal Line Upper Left  to Bottom Right
    //   2, 4, 6 -> Diagonal Line Upper Right to Bottom Left.
    //
    // Notice that, for each "line" we have a start index
    // and a increment of this index. So we defined a function
    // that take those parameters and check if all "spaces" in
    // board are filled by the same player different from None.

    //Horizontal lines.
    if(checkVictoryHelper(0, 1)) return;
    if(checkVictoryHelper(3, 1)) return;
    if(checkVictoryHelper(6, 1)) return;

    //Vertical Lines.
    if(checkVictoryHelper(0, 3)) return;
    if(checkVictoryHelper(1, 3)) return;
    if(checkVictoryHelper(2, 3)) return;

    //Diagonal Lines.
    if(checkVictoryHelper(0, 4)) return;
    if(checkVictoryHelper(2, 2)) return;
}

bool Board::checkVictoryHelper(int initialPos, int increment)
{
    Player p = getPlayerAt(initialPos);
    //Already empty... don't need to continue checking...
    if(p == Player::None)
        return false;

    //Same player at each positions.
    //  Winner is found.
    if(p == getPlayerAt(initialPos + (    increment)) &&
       p == getPlayerAt(initialPos + (2 * increment)))
    {
        m_winner = p;
        return true;
    }

    //Different player at positions.
    return false;
}
