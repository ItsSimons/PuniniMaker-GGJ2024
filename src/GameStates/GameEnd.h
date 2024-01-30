//
// Created by Simon on 25/10/2022.
//

#ifndef PACMANSFML_GAMEEND_H
#define PACMANSFML_GAMEEND_H

#include "../Interfaces/StateTemplate.h"

class GameEnd : public StateTemplate
{
 public:
  explicit GameEnd(GameData& gameData);
  ~GameEnd() override;

  //Game loop
  bool init() override;
  void update(float dt) override;
  void render() override;

  //Keyboard input
  void keyPressed(GameEvent event) override;
  void keyReleased(GameEvent event) override;
  void textEntered(GameEvent event) override;

  //Mouse input
  void mouseMoved(const sf::Vector2f& position) override;
  void mouseReleased(GameEvent event) override;
};

#endif // PACMANSFML_GAMEEND_H
