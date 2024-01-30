//
// Created by Simon on 26/10/2022.
//

#ifndef PACMANSFML_HELPER_H
#define PACMANSFML_HELPER_H

#include <valarray>
namespace helper
{
  /**
  * Takes a text reference and makes a textbox
  *
  * @param[in,out] text reference to the text to modify
  * @param[in] font font you want to use
  * @param[in] string string of text to display
  * @param[in] x, y position on the screen
  * @param[in] size size of the text
  */
  static void makeTextbox(
    sf::Text& text, const sf::Font& font, const std::string& string,
    float pos_x, float pos_y, unsigned int size)
  {
    text.setFont(font);
    text.setString(string);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color(255, 255, 255, 230));
    text.setOrigin(text.getGlobalBounds().width * 0.5f,
                   text.getGlobalBounds().height * 0.57f);
    text.setPosition(pos_x, pos_y);
  }

  /**
  * Takes a text reference and makes a textbox
  *
  * @param[in,out] text reference to the text to modify
  * @param[in] font font you want to use
  * @param[in] string string of text to display
  * @param[in] x, y position on the screen
  * @param[in] size size of the text
  * @param[in] color Color of the text
  */
  static void makeTextbox(
    sf::Text& text, const sf::Font& font, const std::string& string,
    float pos_x, float pos_y, unsigned int size, const sf::Color color)
  {
    text.setFont(font);
    text.setString(string);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setOrigin(text.getGlobalBounds().width * 0.5f,
                   text.getGlobalBounds().height * 0.57f);
    text.setPosition(pos_x, pos_y);
  }
};

#endif // PACMANSFML_HELPER_H
