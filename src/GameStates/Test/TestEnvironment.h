
#ifndef PACMANSFML_TESTENVIRONMENT_H
#define PACMANSFML_TESTENVIRONMENT_H

#include "../../Interfaces/StateTemplate.h"

class TestEnvironment : public StateTemplate
{
 public:
  explicit TestEnvironment(GameData& gameData);
  ~TestEnvironment() override;

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

 private:
  //Class specific methods
  void cursorInitializer();
  void cursorHandler();

  //Card flipping
  sf::Vector2f card_scale = {5, 5};
  void cardFlipper(const float& dt);
  bool flipping = false;
  bool flipped = false;
  float flip_timer = 0;
  float flip_duration = 0.25f;
  float scale_change_per_frame = 0;

  //Testing Cards
  sf::Sprite card_sprite_front;
  sf::Sprite card_sprite_back;

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

  //Debugging
  sf::Text test_text;
};

#endif // PACMANSFML_TESTENVIRONMENT_H
