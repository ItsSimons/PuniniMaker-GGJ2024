#ifndef PACMANSFML_GAMEPLAY_H
#define PACMANSFML_GAMEPLAY_H

#include "../Interfaces/StateTemplate.h"
#include "../Cards/BaseCard.h"

class GamePlay : public StateTemplate
{
 public:
  explicit GamePlay(GameData& gameData);
  ~GamePlay() override;

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

  //card handling
  void centerCards();

 private:
  sf::Sprite background_sprite;
  std::unique_ptr<BaseCard> TestCard = nullptr;

  sf::Sprite draw_pile_sprite;
  sf::Sprite discard_pile_sprite;

  std::vector<std::unique_ptr<BaseCard>> draw_pile;
  std::vector<std::unique_ptr<BaseCard>> discard_pile;
  std::vector<std::unique_ptr<BaseCard>> deck;

  sf::Vector2f draw_pile_position = {0,0};
  sf::Vector2f discard_pile_position = {0,0};
  sf::Vector2f deck_position = {0,0};
  unsigned int card_total = 40;
  unsigned int card_hand = 5;
  float deck_spacing = 15.f;

  sf::Clock draw_clock;
  float draw_delay = 0.50f; //seconds
};

#endif // PACMANSFML_GAMEPLAY_H
