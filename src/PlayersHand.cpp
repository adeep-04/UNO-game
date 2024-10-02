
#include "PlayersHand.h"
#include "cartes.h"
#include <queue>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

class cartes;

PlayersHand::PlayersHand()
{
    ListCarte.resize(10);

    for (int i = 0; i < 10; i++)
    {
        cartes c;
        ListCarte[i]=c.setCard();
    }
    cout << "\n\n========///" << ListCarte.size();
}

int PlayersHand::getScore()
{
    return score;
}

int PlayersHand::getSize()
{
    return ListCarte.size();
}

void PlayersHand::print_carte()const
{
    string color_card[6]{"RED", "GREEN", "BLUE", "YELLOW", "WILD","NON"};
    string value_card[15]{"ZERO", "ONE"," TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "SKIP", "REVERSE", "DRAW_TWO", "WILD_DRAW_FOUR","NON"};

    for(int i = 0;i < ListCarte.size(); i++)
    {
      int colorindex = ListCarte[i].getColor();
      int valueindex = ListCarte[i].getValue();
      cout << "Card " << i << " = " << color_card[colorindex] << " - " << value_card[valueindex] << " | " << "\n====================================\n";
    }
}

void PlayersHand::Delete_card(int num_carte)
{
    vector<cartes>::iterator it = ListCarte.begin() + num_carte;
    int sizee = ListCarte.size();
    ListCarte.erase(it);
    ListCarte.resize(sizee - 1);
    score += 10;
}

void PlayersHand::add_DRAW_tow()
{
    cout << endl << endl << "add tow" << endl << endl;
    ListCarte.resize(ListCarte.size() + 2);
    for (int i = ListCarte.size() - 2; i < ListCarte.size() + 1; i++)
    {
        ListCarte[i] = ListCarte[i].setCard();
    }
    score -= 5;
}

void PlayersHand::add_WILD_DRAW_four(Game_Surface &game)
{
    ListCarte.resize(ListCarte.size()+4);
    for (int i = ListCarte.size() - 4; i < ListCarte.size() + 1; i++)
    {
        ListCarte[i] = ListCarte[i].setCard();
    }
    cout << "Choose the appropriate color 0-RED, 1-GREEN, 2-BLUE, 3-YELLOW" << endl;
    int choose;
    cin >> choose;
    game.WILd((static_cast<Color>(choose)));
    score-=10;
}

void PlayersHand::add_DRAW()
{
    ListCarte.resize(ListCarte.size() + 1);
    int i = (ListCarte.size() - 1);
    ListCarte[i] = ListCarte[i].setCard();
    score -= 3;
}

cartes PlayersHand::card_player(int num_card)
{
    return ListCarte[num_card];
}

PlayersHand::~PlayersHand()
{
    //dtor
}
