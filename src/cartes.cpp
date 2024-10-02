
#include "cartes.h"
#include <queue>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include<string>

using namespace std;

vector<cartes> cartes::deck;

cartes::cartes(){}

cartes::cartes(Color color1, Value value1)
{
  color = color1;
  value = value1;
}

void cartes::createDeck( ) 
{
  for (int color = RED; color <= YELLOW; ++color) 
  {
    // Add 18 cards from 1 to 9 (two of each)
    for (int value = ONE; value <= NINE; ++value) 
    {
      deck.push_back(cartes(static_cast<Color>(color), static_cast<Value>(value)));
      deck.push_back(cartes(static_cast<Color>(color), static_cast<Value>(value)));
    }
    // Add a 0 card for each color
    deck.push_back(cartes(static_cast<Color>(color), ZERO));
    // Add 2 Skip cards for each color
    deck.push_back(cartes(static_cast<Color>(color), SKIP));
    deck.push_back(cartes(static_cast<Color>(color), SKIP));
    // Add 2 Reverse cards for each color
    deck.push_back(cartes(static_cast<Color>(color), REVERSE));
    deck.push_back(cartes(static_cast<Color>(color), REVERSE));
    // Add 2 Draw Two cards for each color
    deck.push_back(cartes(static_cast<Color>(color), DRAW_TWO));
    deck.push_back(cartes(static_cast<Color>(color), DRAW_TWO));
  }
  // Add 4 Wild cards
  for (int i = 0; i < 4; ++i) 
  {
    deck.push_back(cartes(WILD, NON_V));
    deck.push_back(cartes(NON_C, WILD_DRAW_FOUR));
  }
}

cartes cartes::setCard()
{
  // Get a random number between 0 and 107 (inclusive)
  if ((deck.size()) == 0)
  {
    return cartes(NON_C,NON_V);
  }
  int randomCardIndex = rand() % deck.size();
  cartes randomcard =deck[randomCardIndex];
  vector<cartes>::iterator it = deck.begin() + randomCardIndex;
  deck.erase(it);
  return randomcard;
}

void cartes::setColor(Color color1)
{
  color = color1;
}

Color cartes::getColor()const
{
  return color;
}

Value cartes::getValue()const
{
  return value;
}

void Game_Surface::Game_surface (const cartes &carte)
{
  Game_surFace.push(carte);
  Game_surFace.pop();
}

bool Game_Surface::is_valid_card (const cartes &carte)const 
{
  return ((Game_surFace.back().getColor() == carte.getColor()) || (Game_surFace.back().getValue() == carte.getValue()) || (carte.getColor()== WILD) || (carte.getValue() == WILD_DRAW_FOUR));
}

void Game_Surface::WILd(Color color)
{
  Game_surFace.back().setColor(color);
}

void Game_Surface::start_game()
{
  cartes startcarte;
  startcarte = startcarte.setCard();
  Game_surFace.push(startcarte);
}

void Game_Surface::Show_card()
{
  string color_card[6]{"RED", "GREEN", "BLUE", "YELLOW", "WILD","NON_C"};
  string value_card[15]{"ZERO", "ONE"," TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "SKIP", "REVERSE", "DRAW_TWO", "WILD_DRAW_FOUR","NON_V"};
  cout << color_card[(int)Game_surFace.back().getColor()] << " - " << value_card[(int)Game_surFace.back().getValue()] << endl;
}

int cartes::getSize()const
{
  return deck.size();
}
