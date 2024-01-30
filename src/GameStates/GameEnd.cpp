//
// Created by Simon on 25/10/2022.
//

#include "GameEnd.h"

GameEnd::GameEnd(GameData& gameData) : StateTemplate(gameData)
{

}

GameEnd::~GameEnd()
{

}

//Game loop --------------------------------------------------------------------

bool GameEnd::init()
{
  return true;
}

void GameEnd::update(float dt)
{

}

void GameEnd::render()
{

}

//Keyboard input ---------------------------------------------------------------

void GameEnd::keyPressed(GameEvent event)
{

}

void GameEnd::keyReleased(GameEvent event)
{

}

void GameEnd::textEntered(GameEvent event)
{

}

//Mouse input ------------------------------------------------------------------

void GameEnd::mouseMoved(const sf::Vector2f& position)
{

}

void GameEnd::mouseReleased(GameEvent event)
{

}

