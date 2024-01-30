
#ifndef PACMANSFML_GAMEDATA_H
#define PACMANSFML_GAMEDATA_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "ResourceManager.hpp"
#include "Helper.h"

enum GameStates
{
  GAME_START = 0,
  GAME_PLAY = 1,
  GAME_END = 2,
  TEST_ENVIRONMENT = 3,
};

//Game-data struct, stores data that has to be accessible everywhere in code
struct GameData
{
  //Main SFML components
  sf::RenderWindow* window = nullptr;
  sf::View* default_view = nullptr;

  //resources handler and default font
  ResourceManager* resources = nullptr;
  const sf::Font* default_font = nullptr;

  //current game state
  GameStates game_state = GAME_PLAY;

  //Card mesurments
  sf::Vector2f text_scale = {1,1};
  sf::Vector2f card_scale = {5,5};
  sf::Vector2f draw_pile_scale = {6,6};
  sf::Vector2f discard_pile_scale = {6,6};

};


#endif // PACMANSFML_GAMEDATA_H
