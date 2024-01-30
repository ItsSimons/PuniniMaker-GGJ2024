//
// Created by Simon on 25/10/2022.
//

#include "GameStart.h"

GameStart::GameStart(GameData& gameData) : StateTemplate(gameData)
{

}

GameStart::~GameStart()
{

}

//Game loop --------------------------------------------------------------------

bool GameStart::init()
{
  return true;
}

void GameStart::update(float dt)
{

}

void GameStart::render()
{

}

//Keyboard input ---------------------------------------------------------------

void GameStart::keyPressed(GameEvent event)
{

}

void GameStart::keyReleased(GameEvent event)
{

}

void GameStart::textEntered(GameEvent event)
{

}

//Mouse input ------------------------------------------------------------------

void GameStart::mouseMoved(const sf::Vector2f& position)
{

}

void GameStart::mouseReleased(GameEvent event)
{

}
