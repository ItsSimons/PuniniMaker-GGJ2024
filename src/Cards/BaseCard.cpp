//
// Created by Simon on 27/01/2024.
//

#include "BaseCard.h"

BaseCard::BaseCard(GameData& gameData) : data(gameData)
{
  card_scale = data.card_scale;
  text_scale = data.text_scale;
  init();
}

BaseCard::~BaseCard()
= default;

//Game loop --------------------------------------------------------------------

bool BaseCard::init()
{
  helper::makeTextbox(
    card_text, *data.default_font,
    "Hello\nHello\nHello\nHello\nHello", 0, 0, font_size, sf::Color::Black);

  card_sprite_front.setTexture(
    data.resources->getTexture("toastFront.png"));
  card_sprite_front.setOrigin(
    card_sprite_front.getGlobalBounds().width / 2,
    card_sprite_front.getGlobalBounds().height / 2);
  card_sprite_front.scale(card_scale);

  card_sprite_back.setTexture(
    data.resources->getTexture("toastBack1.png"));
  card_sprite_back.setOrigin(
    card_sprite_back.getGlobalBounds().width / 2,
    card_sprite_back.getGlobalBounds().height / 2);
  //card_sprite_back.scale(card_scale);
  card_sprite_back.setScale(0, card_scale.y);

  setCardPosition({(data.window->getSize().x * 0.5f),
                   (data.window->getSize().y * 0.5f)});

  card_position = {(data.window->getSize().x * 0.5f),
                    (data.window->getSize().y * 0.5f)};

  scale_change_per_frame_card = card_scale.x / (flip_duration * 60); //60 is the fps
  scale_change_per_frame_text = text_scale.x / (flip_duration * 60);

  movement_clock.restart();

  return true;
}

void BaseCard::update(float dt)
{
  flipCard(dt);
  highlightCard(dt);
  easeOutMove();
}

void BaseCard::render()
{
  data.window->draw(card_sprite_front);
  data.window->draw(card_text);
  data.window->draw(card_sprite_back);
}

//Keyboard input ---------------------------------------------------------------

void BaseCard::mouseMoved(const sf::Vector2f& position)
{
  mouse_position = position;
  auto mouse_pos = static_cast<sf::Vector2i>(position);

  if(card_sprite_front.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y) ||
     card_sprite_back.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
    hovering = true;
  else
    hovering = false;
}

void BaseCard::mouseReleased(GameEvent event)
{
  if(event.mouseButton.button == sf::Mouse::Button::Left && hovering)
  {
    if(!flipping) flipping = true;
  }

  if(event.mouseButton.button == sf::Mouse::Button::Right)
  {
    sendCardTo(mouse_position);
  }
}

// Card movement ---------------------------------------------------------------

void BaseCard::setCardPosition(sf::Vector2f position)
{
  card_sprite_front.setPosition(position.x, position.y);
  card_sprite_back.setPosition(position.x, position.y);
  card_position = position;
  card_text.setPosition(position);
}

void BaseCard::sendCardTo(const sf::Vector2f& position)
{
  moving = true;
  movement_duration = 2.f;
  start_position = card_position;
  end_position = position;
  movement_clock.restart();
}

void BaseCard::throwCardTo(const sf::Vector2f& position)
{
  moving = true;
  movement_duration = 1.f;
  start_position = card_position;
  end_position = position;
  movement_clock.restart();
}

//getters and setters ----------------------------------------------------------

void BaseCard::setText(const std::string& text)
{
  card_text.setString(text);
}

std::string BaseCard::getText()
{
  return card_text.getString();
}

//Card flipping ----------------------------------------------------------------

void BaseCard::flipCard(const float& dt)
{
  if(flipping)
  {
    if(!flipped)
    {
      if(flip_timer < flip_duration)
      {
        if(card_sprite_front.getScale().x > error_rounding_pos && card_sprite_front.getScale().x <= card_scale.x)
        {
          card_sprite_front.setScale(
            card_sprite_front.getScale().x - scale_change_per_frame_card, card_scale.y);
        }

        if(card_text.getScale().x > 0.01 && card_text.getScale().x <= 1)
        {
          card_text.setScale(
            card_text.getScale().x - scale_change_per_frame_text, text_scale.y);
        }
      }
      else
      {
        if(card_sprite_back.getScale().x >= error_rounding_neg && card_sprite_back.getScale().x < card_scale.x + error_rounding_pos)
        {
          card_sprite_back.setScale(
            card_sprite_back.getScale().x + scale_change_per_frame_card, card_scale.y);
        }
      }
    }
    else
    {
      if(flip_timer < flip_duration)
      {
        if(card_sprite_back.getScale().x > error_rounding_pos && card_sprite_back.getScale().x <= card_scale.x)
        {
          card_sprite_back.setScale(
            card_sprite_back.getScale().x - scale_change_per_frame_card, card_scale.y);
        }
      }
      else
      {
        if(card_sprite_front.getScale().x >= error_rounding_neg && card_sprite_front.getScale().x < card_scale.x + error_rounding_pos)
        {
          card_sprite_front.setScale(
            card_sprite_front.getScale().x + scale_change_per_frame_card, card_scale.y);
        }


        if(card_text.getScale().x >= 0 && card_text.getScale().x < 1.01)
        {
          card_text.setScale(
            card_text.getScale().x + scale_change_per_frame_text, text_scale.y);
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

void BaseCard::highlightCard(const float& dt)
{
  if(hovering && !raised)
  {
    sendCardTo({card_position.x, card_position.y - raise_amount});
    raised = true;
  }
  else if (raised && !hovering)
  {
    sendCardTo({card_position.x, card_position.y + raise_amount});
    raised = false;
  }
}

float BaseCard::easeOutExpo(float t)
{
  return (t == 1.0) ? 1.0 : 1 - pow(2, -10 * t);
}

void BaseCard::easeOutMove()
{
  float time = movement_clock.getElapsedTime().asSeconds();

  if (time < movement_duration && moving)
  {
    float t = time / movement_duration;
    float easedT = easeOutExpo(t);

    // Interpolate position
    sf::Vector2f new_pos = start_position + (end_position - start_position) * easedT;
    setCardPosition(new_pos);
  }
  else
  {
    moving = false;
  }
}

sf::Sprite* BaseCard::getSprite()
{
  return &card_sprite_front;
}
