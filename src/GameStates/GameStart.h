//
// Created by Simon on 25/10/2022.
//

#ifndef PACMANSFML_GAMESTART_H
#define PACMANSFML_GAMESTART_H

#include "../Interfaces/StateTemplate.h"

class GameStart : public StateTemplate
{
 public:
  explicit GameStart(GameData& gameData);
  ~GameStart() override;

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

#endif // PACMANSFML_GAMESTART_H
