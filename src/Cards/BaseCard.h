
#ifndef GGJ2024_BASECARD_H
#define GGJ2024_BASECARD_H

#include "../Components/GameData.h"
using GameEvent = const sf::Event&;

class BaseCard
{
 public:
  explicit BaseCard(GameData& gameData);
  ~BaseCard();

  //Game loop
  bool init();
  void update(float dt);
  void render();

  //Mouse input
  void mouseMoved(const sf::Vector2f& position);
  void mouseReleased(GameEvent event);

  //Cards movement
  void setCardPosition(sf::Vector2f position);
  void sendCardTo(const sf::Vector2f& position);
  void throwCardTo(const sf::Vector2f& position);

  //Set/Get
  void setText(const std::string& text);
  std::string getText();
  sf::Sprite* getSprite();

  bool flipping = false;
  bool flipped = false;

 private:
  void flipCard(const float& dt);
  void highlightCard(const float& dt);

  sf::Sprite card_sprite_front;
  sf::Sprite card_sprite_back;
  sf::Text card_text;

  //Card adjusting
  sf::Vector2f card_scale = {0, 0};
  sf::Vector2f text_scale = {0, 0};
  sf::Vector2f card_position = {0,0};
  float error_rounding_pos   = 0.1f;
  float error_rounding_neg   = -0.01f;
  float font_size = 30;

  bool hovering = false;
  bool raised = false;
  int raise_amount = 50;

  float flip_timer = 0;
  float flip_duration = 0.25f;
  float scale_change_per_frame_card = 0;
  float scale_change_per_frame_text = 0;

  GameData& data;

  //Movement
  void easeOutMove();
  float easeOutExpo(float t);

  sf::Vector2f start_position = {0,0};
  sf::Vector2f end_position = {0,0};
  sf::Vector2f mouse_position = {0,0};

  sf::Clock movement_clock;
  float movement_duration = 1.f;
  bool moving = false;
};

#endif // GGJ2024_BASECARD_H
