#include "Components/GameData.h"
#include "GameInstance.h"

int main()
{
  // create window and set up
  sf::RenderWindow window(sf::VideoMode(1281, 900), "PUNini-maker");
  window.setMouseCursorVisible(false);
  window.setFramerateLimit(60);

  //memorizes the default view
  sf::View default_view = window.getDefaultView();

  //Instantiates the resource handler
  ResourceManager resource_manager((std::string)"Data");
  sf::Font default_font = resource_manager.getFont("Born2bSportyFS.otf");

  //Setting up an instance of GameData, as a pointer, so it can be accessed
  //easily in code
  GameData game_data =
    {
      &window,
      &default_view,
      &resource_manager,
      &default_font
    };

  //initialise an instance of the game class
  GameInstance game(game_data);

  //run the init function of the game class and check it all initialises ok
  if (!game.init())
  {
    std::cout << "\nInitialization failed! Are you sure all needed components have "
                 "been provided?" << std::endl;
    return 0;
  }

  // A Clock starts counting as soon as it's created
  sf::Clock clock;

  // Game loop: run the program as long as the window is open
  while (window.isOpen())
  {
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event{};

    //calculate delta time
    sf::Time time = clock.restart();
    float dt = time.asSeconds();

    //'process inputs' element of the game loop
    while (window.pollEvent(event))
    {
      //GameEvent handler
      switch (event.type)
      {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::TextEntered:
          game.textEntered(event);
          break;
        case sf::Event::KeyPressed:
          game.keyPressed(event);
          break;
        case sf::Event::KeyReleased:
          game.keyReleased(event);
          break;
        case sf::Event::MouseButtonReleased:
          game.mouseReleased(event);
          break;
        case sf::Event::MouseMoved:
          game.mouseMoved(event);
          break;
      }
    }

    //'update' element of the game loop
    game.update(dt);

    // Nothing Rendered? No worries! Black screen!
    window.clear(sf::Color::Black);

    //'render' element of the game loop
    game.render();
    window.display();
  }

  return 0;
}
