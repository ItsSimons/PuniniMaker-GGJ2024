//
// Created by Simon on 25/10/2022.
//

#ifndef PACMANSFML_STATETEMPLATE_H
#define PACMANSFML_STATETEMPLATE_H

#include "../Components/GameData.h"

using GameEvent = const sf::Event&;

class StateTemplate
{
 public:
  explicit StateTemplate(GameData& game_data) : data(game_data){};
  virtual ~StateTemplate() = default;

  //Game loop
  virtual bool init() = 0;
  virtual void update(float dt) = 0;
  virtual void render() = 0;

  //Keyboard input
  virtual void keyPressed(GameEvent event) = 0;
  virtual void keyReleased(GameEvent event) = 0;
  virtual void textEntered(GameEvent event) = 0;

  //Mouse input
  virtual void mouseMoved(const sf::Vector2f& position) = 0;
  virtual void mouseReleased(GameEvent event) = 0;

 protected:
  //Reference to GameData for all child classes
  GameData& data;
};

#endif // PACMANSFML_STATETEMPLATE_H
