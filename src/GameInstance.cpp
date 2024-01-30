
#include "GameInstance.h"

GameInstance::GameInstance(GameData& game_data)
  : data(game_data)
{
  //Seeds the generator
  srand(time(nullptr));

  //Allocates each of the game states on the heap
  state_array[GAME_START] = std::make_unique<GameStart>(data);
  state_array[GAME_PLAY] = std::make_unique<GamePlay>(data);
  state_array[GAME_END] = std::make_unique<GameEnd>(data);
  state_array[TEST_ENVIRONMENT] = std::make_unique<TestEnvironment>(data);
}

//Game loop --------------------------------------------------------------------

bool GameInstance::init()
{
  //Runs the Init in each of the game states
  for(auto& state : state_array)
  {
    if(!state->init())
    {
      std::cout << "\nOne the game states failed initialization!" << std::endl;
      return false;
    }
  }

  //Inits the cursor custom sprite
  cursorInitializer();

  return true;
}

void GameInstance::update(float dt)
{
  cursorHandler();
  state_array[data.game_state]->update(dt);
}

void GameInstance::render()
{
  state_array[data.game_state]->render();
  data.window->draw(cursor_sprite);
}

//Keyboard input ---------------------------------------------------------------

void GameInstance::keyPressed(GameEvent event)
{
  //Temporary to close with Escape
  if(event.key.code == sf::Keyboard::Escape)
  {
    data.window->close();
  }

  state_array[data.game_state]->keyPressed(event);
}

void GameInstance::keyReleased(GameEvent event)
{
  state_array[data.game_state]->keyReleased(event);
}

void GameInstance::textEntered(GameEvent event)
{
  state_array[data.game_state]->textEntered(event);
}

//Mouse input ------------------------------------------------------------------

void GameInstance::mouseMoved(GameEvent event)
{
  //gets the mouse position and shares it
  sf::Vector2f position = static_cast<sf::Vector2f>(
    sf::Mouse::getPosition(*data.window));

  //a little offset is applied because it was a little sluggish without
  cursor_sprite.setPosition(position.x - 6, position.y - 5);

  state_array[data.game_state]->mouseMoved(position);
}

void GameInstance::mouseReleased(GameEvent event)
{
  state_array[data.game_state]->mouseReleased(event);
}

//Cursor -----------------------------------------------------------------------

void GameInstance::cursorInitializer()
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

void GameInstance::cursorHandler()
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
