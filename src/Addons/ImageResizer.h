//
// Created by Simon on 16/10/2022.
//

#ifndef PACMANSFML_IMAGERESIZER_H
#define PACMANSFML_IMAGERESIZER_H
#include <SFML/Graphics.hpp>

class ImageResizer
{
 public:
  ImageResizer();
  ~ImageResizer();
  void resizeImage(sf::Image& image, int size);

 private:
  sf::Vector2<unsigned int> oldSize;
  sf::Vector2<unsigned int> newSize;
  std::vector<unsigned int> pixelData;
};

#endif // PACMANSFML_IMAGERESIZER_H
