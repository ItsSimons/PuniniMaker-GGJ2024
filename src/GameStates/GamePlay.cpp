#include "GamePlay.h"

GamePlay::GamePlay(GameData& gameData) : StateTemplate(gameData)
{

}

GamePlay::~GamePlay()
= default;

//Game loop --------------------------------------------------------------------

bool GamePlay::init()
{
  TestCard = std::make_unique<BaseCard>(data);

  background_sprite.setTexture(data.resources->getTexture("Panini-maker.png"));
  background_sprite.setScale(2.47f,2.47f);

  draw_clock.restart();

  draw_pile_position = {data.window->getSize().x * 0.07f, data.window->getSize().y * 0.87f};
  discard_pile_position = {data.window->getSize().x * 0.93f, data.window->getSize().y * 0.87f};

  draw_pile_sprite.setTexture(data.resources->getTexture("toastFront.png"));
  draw_pile_sprite.setOrigin(
    draw_pile_sprite.getGlobalBounds().width / 2,
    draw_pile_sprite.getGlobalBounds().height / 2);
  draw_pile_sprite.setScale(data.draw_pile_scale);
  draw_pile_sprite.setPosition(draw_pile_position);

  discard_pile_sprite.setTexture(data.resources->getTexture("toastFront.png"));
  discard_pile_sprite.setOrigin(
    discard_pile_sprite.getGlobalBounds().width / 2,
    discard_pile_sprite.getGlobalBounds().height / 2);
  discard_pile_sprite.setScale(data.discard_pile_scale);
  discard_pile_sprite.setPosition(discard_pile_position);

  for (int i = 0; i < card_total; ++i)
  {
    draw_pile.push_back(std::make_unique<BaseCard>(data));
    draw_pile[i]->setCardPosition(draw_pile_position);
    draw_pile[i]->setText("Card\n Num:\n" + std::to_string(i));
    draw_pile[i]->flipping = true;
  }

  return true;
}

void GamePlay::update(float dt)
{
  if(!draw_pile.empty())
  {
    if(deck.size() < card_hand)
    {
      if(draw_clock.getElapsedTime().asMilliseconds() > draw_delay * 1000)
      {
        //Draw a card
        deck.push_back(std::move(draw_pile.front()));
        draw_pile.erase(draw_pile.begin());
        draw_clock.restart();

        deck.back()->flipping = true;
        centerCards();
      }
    }
    else if (draw_pile.empty())
    {
      discard_pile.insert(discard_pile.end(),
                          std::make_move_iterator(draw_pile.begin()),
                          std::make_move_iterator(draw_pile.end()));

      draw_pile.clear();
    }
  }

  for (const auto& card : deck)
  {
    card->update(dt);
  }

  TestCard->update(dt);
}

void GamePlay::render()
{
  data.window->draw(background_sprite);
  data.window->draw(draw_pile_sprite);
  data.window->draw(discard_pile_sprite);

  if(!draw_pile.empty()) draw_pile.front()->render();

  for (const auto& card : deck)
  {
    card->render();
  }

  //TestCard->render();
}

//Keyboard input ---------------------------------------------------------------

void GamePlay::keyPressed(GameEvent event)
{

}

void GamePlay::keyReleased(GameEvent event)
{

}

void GamePlay::textEntered(GameEvent event)
{

}

//Mouse input ------------------------------------------------------------------

void GamePlay::mouseMoved(const sf::Vector2f& position)
{
  for (const auto& card : deck)
  {
    card->mouseMoved(position);
  }
}

void GamePlay::mouseReleased(GameEvent event)
{
  for (const auto& card : deck)
  {
    card->mouseReleased(event);
  }

  if(event.mouseButton.button == sf::Mouse::Button::Right)
  {
    centerCards();
  }
}

//Card handling ----------------------------------------------------------------

void GamePlay::centerCards()
{
  std::cout << "Centering cards" << std::endl;

  int num_of_cards = deck.size();
  if (num_of_cards == 0) return;

  float card_width = deck.back()->getSprite()->getGlobalBounds().width;
  float total_width = num_of_cards * card_width + (num_of_cards - 1) * deck_spacing;

  float start_x   = (data.window->getSize().x - total_width) / 2.0f;
  float y_pos     = data.window->getSize().y / 2.0f; // Adjust y position as needed

  for (int i = 0; i < num_of_cards; ++i)
  {
    deck[i]->throwCardTo({start_x + i * (card_width + deck_spacing), y_pos});
  }
}
