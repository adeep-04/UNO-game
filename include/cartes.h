#ifndef CARTES_H
#define CARTES_H
#include <queue>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include<string>

using namespace std;

enum Color { RED, GREEN, BLUE, YELLOW, WILD,NON_C };
enum Value { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, SKIP, REVERSE, DRAW_TWO, WILD_DRAW_FOUR ,NON_V};

class PlayersHand;

class cartes
{
    private:
        Color color;
        Value value;
        static  vector<cartes> deck;

    public:
        cartes();
        cartes(Color color1, Value value1 );
        void createDeck();
        cartes setCard();
        void setColor(Color color1);
        Color getColor()const;
        Value getValue()const;
        int getSize()const;

        friend class Game_Surface;

    protected:
};

class Game_Surface
{
  public:
    queue<cartes> Game_surFace;
    void Game_surface (const cartes &carte);
    bool is_valid_card (const cartes &carte)const;
    void start_game();
    void WILd(Color color);
    void Show_card();
    friend class cartes;
};

#endif // CARTES_H
