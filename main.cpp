#include <iostream>
#include <cstdlib>
#include <ctime>
#include "cartes.h"
#include <queue>
#include "PlayersHand.h"
#include <string>
#include <map>

using namespace std;

void Direction_indirect(map<int,PlayersHand> &Players, int P_dirction, int &theRole, Game_Surface &game, int num_players);
int Check_number_of_players();
void Create_players(map<int,PlayersHand> &Players, int num_Players);
void SKiP_card(int &the_role, int Play_direction, int num_Players);
void Direction_game(int &Play_direction);
void Direction_direct(map<int,PlayersHand> &Players, int &theRole, Game_Surface &game, int num_players, int &Play_direction, cartes c);
int The_winner(map<int,PlayersHand> &Players, int num_players);

int main() 
{
    srand(time(nullptr));
    map<int,PlayersHand> Players;
    int Play_direction = 1;
    cout << "Welcome to the game of Uno "<< endl;
    cout << "Select number of players (2 to 4): ";
    int Choose = Check_number_of_players();
    cartes c;
    c.createDeck();
    Create_players(Players, Choose);
    Game_Surface game;
    game.start_game();
    int TheRole = 0;
    Direction_direct(Players,TheRole,game, Choose,Play_direction,c);

    int winner = The_winner(Players, Choose);
    cout << "The winner is " << winner + 1 << endl;
    cout << "The number of points he collected is "<< Players[winner].getScore();
    return 0;
}

int Check_number_of_players()
{
 do
 {
    int choose;
    cin >> choose;
    if (choose >= 2 && choose <= 4)
    {
        return choose;
    }
 }
 while(true);

}

void Create_players(map<int,PlayersHand> &Players, int num_Players)
{
    for (int i=0;i<num_Players;i++)
    {
        Players[i];
    }
}

bool Game_over(map<int,PlayersHand> &Players, int num_Players, cartes c)
{
    for(int i = 0; i < num_Players; i++)
    {
        if (Players[i].getSize() == 0 || c.getSize() == 0 )
        {
            return 0;
        }
    }
    return 1;
}

void SKiP_card(int &the_role, int Play_direction, int num_Players)
{
    if (Play_direction == 1)
    {
        if (the_role == (num_Players - 1) && num_Players != 2)
        {
            the_role = 0;
        }
        else if (the_role == (num_Players - 2) && num_Players != 2)
        {
         the_role =- 1;
        }
        else if (the_role < (num_Players - 2) && num_Players !=2 )
        {
            the_role++;
        }
        else if (num_Players == 2)
        {
            the_role--;
        }
    }

    if (Play_direction == -1)
    {
        if(the_role == 0 && num_Players != 2)
        {
            the_role = num_Players - 1;
        }
        else if (the_role == 1 && num_Players != 2)
        {
            the_role = num_Players;
        }
        else if (the_role > 1 && num_Players != 2)
        {
            the_role--;
        }
        else if (num_Players == 2)
        {
            the_role++;
        }
    }
}

void Direction_game(int &Play_direction)
{
    if (Play_direction == 1)
    {
        Play_direction =- 1;
    }
    else if (Play_direction == -1)
    {
        Play_direction = 1;
    }
}

void Direction_direct(map<int,PlayersHand> &Players, int &theRole, Game_Surface &game, int num_players, int &Play_direction, cartes c)
{
   while(Game_over(Players, num_players, c))
   {
        cout << endl << endl << "The card on the table is: ";
        game.Show_card();
        cout << "====================================================" << endl;
        cout << "Player No" << theRole + 1 <<" has the following cards: \n==============================\n";
        Players[theRole].print_carte();
        do
        {
            cout << "Select the card number you want to play." << endl;
            cout << "If you do not have a card for the game, enter a random card.\n";
            int num_card;
            cin >> num_card;
            cartes cartplay = Players[theRole].card_player(num_card);
            if (!(game.is_valid_card(cartplay)))
            {
            cout << "Invalid card" << endl;
            cout << "If you do not have a card for the game, enter 1. If you make a mistake, enter 0.\n";
            int x;
            cin >> x;
            if (x)
            {
                Players[theRole].add_DRAW();
                break;
            }
            continue;
            }
            game.Game_surface(cartplay);
            Players[theRole].Delete_card(num_card);
            if (cartplay.getColor() == WILD)
            {
                cout << "Choose the appropriate color 0-RED, 1-GREEN, 2-BLUE, 3-YELLOW" << endl;
                int choose;
                cin >> choose;
                game.WILd((static_cast<Color>(choose)));
                break;
            }
            if (cartplay.getValue() == SKIP)
            {
                cout << "Skip card has been used." << endl;
                SKiP_card(theRole, Play_direction, num_players);
                break;
            }

            if (cartplay.getValue() == DRAW_TWO)
            {
                if (Play_direction == 1)
                {
                    if (theRole == num_players - 1)
                    {
                        Players[0].add_DRAW_tow();

                    }
                    else
                    {
                        Players[theRole + 1].add_DRAW_tow();
                    }
                }
                if (Play_direction == -1)
                {
                    if (theRole == 0)
                    {
                        Players[num_players - 1].add_DRAW_tow();
                    }
                    else
                    {
                        Players[theRole - 1].add_DRAW_tow();
                    }
                }
            }           

            if (cartplay.getValue()==WILD_DRAW_FOUR)
            {
                if (theRole == num_players - 1)
                {
                    Players[0].add_WILD_DRAW_four(game);
                }
                else
                {
                    Players[theRole + 1].add_WILD_DRAW_four(game);
                }
            }
            if(cartplay.getValue() == REVERSE)
            {
                cout << "==== reverse card =======\n";
                Direction_game(Play_direction);
                break;
            }

            if(game.is_valid_card(cartplay))
            {
                break;
            }
        }
        while (true);
        if (Play_direction == 1)
        {
            theRole++;
        }
        if (Play_direction == -1)
        {
            theRole--;
        }
        if ((theRole > num_players - 1) && (Play_direction == 1))
        {
            theRole = 0;
        }
        if (theRole == -1 && Play_direction == -1)
        {
            theRole = num_players - 1;
        }
    }
}

int The_winner(map<int, PlayersHand> &Players, int num_players)
{
    for(int i = 0; i < num_players; i++)
    {
        if (Players[i].getSize() == 0)
        {
            return i;
        }
    }
    return 0;
}
