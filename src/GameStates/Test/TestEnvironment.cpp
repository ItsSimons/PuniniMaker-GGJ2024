//
// Created by Simon on 25/10/2022.
//

#include "TestEnvironment.h"

TestEnvironment::TestEnvironment(GameData& gameData) : StateTemplate(gameData)
{

}

TestEnvironment::~TestEnvironment()
= default;

//Game loop --------------------------------------------------------------------

bool TestEnvironment::init()
{
  //Inits the cursor custom sprite
  cursorInitializer();

  helper::makeTextbox(
    test_text, *data.default_font,
    "HELLO", data.window->getSize().x / 2, data.window->getSize().y / 2, 150, sf::Color::Red);

  card_sprite_front.setTexture(
    data.resources->getTexture("card_front.png"));
  card_sprite_front.setOrigin(
    card_sprite_front.getGlobalBounds().width / 2,
    card_sprite_front.getGlobalBounds().height / 2);
  card_sprite_front.setPosition(
    data.window->getSize().x / 2,
    data.window->getSize().y / 2);
  card_sprite_front.scale(card_scale);

  card_sprite_back.setTexture(
    data.resources->getTexture("card_back.png"));
  card_sprite_back.setOrigin(
    card_sprite_back.getGlobalBounds().width / 2,
    card_sprite_back.getGlobalBounds().height / 2);
  card_sprite_back.setPosition(
    data.window->getSize().x / 2,
    data.window->getSize().y / 2);
  //card_sprite_back.scale(card_scale);
  card_sprite_back.setScale(0, card_scale.y);

  scale_change_per_frame = card_scale.x / (flip_duration * 60); //60 is the fps
  std::cout << scale_change_per_frame << std::endl;

  return true;
}
void TestEnvironment::update(float dt)
{
  //updates the custom cursor
  cursorHandler();
  cardFlipper(dt);
}

void TestEnvironment::render()
{
  data.window->draw(card_sprite_front);
  data.window->draw(card_sprite_back);

  data.window->draw(test_text);
  data.window->draw(cursor_sprite);
}

//Keyboard input ---------------------------------------------------------------

void TestEnvironment::keyPressed(GameEvent event)
{

}

void TestEnvironment::keyReleased(GameEvent event)
{
  if(event.key.code == sf::Keyboard::A ||
      event.key.code == sf::Keyboard::Left)
  {
    if(!flipping) flipping = true;
  }
}

void TestEnvironment::textEntered(GameEvent event)
{

}

//Mouse input ------------------------------------------------------------------

void TestEnvironment::mouseMoved(const sf::Vector2f& position)
{
  //a little offset is applied because it was a little sluggish without
  cursor_sprite.setPosition(position.x - 6, position.y - 5);
}

void TestEnvironment::mouseReleased(GameEvent event)
{

}

//Cursor handling an animation -------------------------------------------------

void TestEnvironment::cursorInitializer()
{
  //Modify those 2 values to adapt a new cursor sprite
  cursor_sections = 5;
  cursor_frame_time = 0.20f;

  //Loads the sprite cursor
  cursor_sprite.setTexture(
    data.resources->getTexture("cursor.png"));

  //Adjusts the recting to the amount of sections
  cursor_width = static_cast<int>(cursor_sprite.getGlobalBounds().width / cursor_sections);
  cursor_height = static_cast<int>(cursor_sprite.getGlobalBounds().height);
  cursor_rect_min = 0;
  cursor_rect_max = static_cast<int>(cursor_width * cursor_sections);

  //Rects the sprite tile sheet
  cursor_rect = sf::IntRect(0,
                           0,
                           cursor_width,
                           cursor_height);
  //Applies the rect
  cursor_sprite.setTextureRect(cursor_rect);
}

void TestEnvironment::cursorHandler()
{
  //every cursor_frame_time changes the rect with the next
  if(cursor_clock.getElapsedTime().asSeconds() > cursor_frame_time)
  {
    if(cursor_rect.left >= cursor_rect_max)
    {
      cursor_rect.left = cursor_rect_min;
    }

    cursor_sprite.setTextureRect(cursor_rect);
    cursor_rect.left += cursor_width;
    cursor_clock.restart();
  }
}

//Card flipping animation ------------------------------------------------------

void TestEnvironment::cardFlipper(const float& dt)
{
  if(flipping)
  {
    if(!flipped)
    {
      if(flip_timer < flip_duration)
      {
        if(card_sprite_front.getScale().x > 0.1 && card_sprite_front.getScale().x <= 5)
        {
          card_sprite_front.setScale(
            card_sprite_front.getScale().x - scale_change_per_frame, card_scale.y);
        }
      }
      else
      {
        if(card_sprite_back.getScale().x >= 0 && card_sprite_back.getScale().x < 5.1)
        {
          card_sprite_back.setScale(
            card_sprite_back.getScale().x + scale_change_per_frame, card_scale.y);
        }
      }
    }
    else
    {
      if(flip_timer < flip_duration)
      {
        if(card_sprite_back.getScale().x > 0.1 && card_sprite_back.getScale().x <= 5)
        {
          card_sprite_back.setScale(
            card_sprite_back.getScale().x - scale_change_per_frame, card_scale.y);
        }
      }
      else
      {
        if(card_sprite_front.getScale().x >= 0 && card_sprite_front.getScale().x < 5.1)
        {
          card_sprite_front.setScale(
            card_sprite_front.getScale().x + scale_change_per_frame, card_scale.y);
        }
      }
    }

    flip_timer += dt;

    if(flip_timer > flip_duration * 2)
    {
      flip_timer = 0;
      flipping = false;
      flipped = !flipped;
      return;
    }
  }
}

