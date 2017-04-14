#ifdef CORE_TICTACTOE_TEST_GAME

#include <iostream>
#include "CoreTicTacToe.h"

#include <sstream>
#include <cstdlib>

using namespace std;
USING_NS_CORETTT;


std::string winner2Str(Player p)
{
    if(p == Player::X)
        return "Player One";
    if(p == Player::O)
        return "Player Two";
    else
        return "Tie";
}

int main()
{
    int gameIndex = 1;
    while(1)
    {
        auto core = GameCore(
            Player::X,
            GameMode::Single,
            AIStrength::Medium,
            10
        );

        cout << "Game: " << gameIndex << endl;
        cout << "-----------------------------------------------------" << endl;
        while(core.getStatus() == CoreGame::Status::Continue)
        {
            cout << core.ascii() << endl;

            if(core.getCurrentPlayer() == Player::X)
            {
                int pos;
                cout << "Pos: ";
                cin >> pos;

                core.makeMove(pos);
            }
            else
            {
                int i = core.getAIMove();
                cout << "AI Decided: " << i << endl;
                core.makeMove(i);
                cout << core.ascii() << endl;

                int a = 10;
            }
        }

        cout << core.ascii() << endl;
        cout << "Winner is: " << winner2Str(core.getWinnerPlayer()) << endl;
        cout << "-----------------------------------------------------" << endl;

        if(core.getWinnerPlayer() != Player::None)
        {
            int a = 10;
            int b =100;
        }

        gameIndex++;
     }

}

#endif //CORE_TICTACTOE_TEST_GAME
