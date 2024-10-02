#ifndef PLAYERSHAND_H
#define PLAYERSHAND_H

#include <queue>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include<string>

using namespace std;

class cartes;
class Game_Surface;

class PlayersHand
{
    private:
        int score=0;
        vector<cartes> ListCarte;
    public:
        PlayersHand();
        int getScore();
        int getSize();
        void print_carte()const;
        void Delete_card(int num_carte);
        void add_DRAW_tow();
        void add_DRAW();
        void add_WILD_DRAW_four(Game_Surface &game);
        cartes card_player(int num_card);
        ~PlayersHand();

    protected:
};

#endif // PLAYERSHAND_H
