
#ifndef PACMANSFML_GAMEINSTANCE_H
#define PACMANSFML_GAMEINSTANCE_H

#include "GameStates/GameEnd.h"
#include "GameStates/GamePlay.h"
#include "GameStates/GameStart.h"
#include "GameStates/Test/TestEnvironment.h"

#include "array"

class GameInstance
{
 public:
  explicit GameInstance(GameData& game_data);
  ~GameInstance() = default;

  //Game loop
  bool init();
  void update(float dt);
  void render();

  //Keyboard input
  void keyPressed(GameEvent event);
  void keyReleased(GameEvent event);
  void textEntered(GameEvent event);

  //Mouse input
  void mouseMoved(GameEvent event);
  void mouseReleased(GameEvent event);

 private:
  void cursorInitializer();
  void cursorHandler();

  //Mouse sprite & texture
  sf::Sprite cursor_sprite;
  sf::Clock cursor_clock;
  sf::IntRect cursor_rect;
  //Cursor animation data
  int cursor_width  = 0;
  int cursor_height = 0;
  int cursor_rect_min = 0;
  int cursor_rect_max = 0;
  float cursor_sections = 0;
  float cursor_frame_time = 0;

  //Game states array
  std::array<std::unique_ptr<StateTemplate>, 4> state_array{};
  GameData& data;
};

#endif // PACMANSFML_GAMEINSTANCE_H
