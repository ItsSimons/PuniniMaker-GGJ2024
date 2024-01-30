//
// Created by Simon on 16/10/2022.
//

#include "ImageResizer.h"
#include "iostream"

ImageResizer::ImageResizer() = default;

ImageResizer::~ImageResizer() = default;

//SFML does not have an image resizer, so I thought to myself, why not making one?
//This ain't going to be nothing fancy but serves the purpose of duplicating/halving
//the resolution of an image
//The int size is the multiple of how many times it has to be increased/decreased
void ImageResizer::resizeImage(sf::Image& image, int size)
{
  oldSize = image.getSize();

  //can't work propely if it is uneven, this cuts it down
  if(oldSize.x % 2 != 0)
  {
    oldSize.x--;
  }

  if(oldSize.y % 2 != 0)
  {
    oldSize.y--;
  }

  //Decreases the image
  if(size > 0)
  {
    newSize.x = oldSize.x / 2;
    newSize.y = oldSize.y / 2;
    std::cout << "new image size: " << newSize.x << " - " << newSize.y << std::endl;

    pixelData.clear();

    //takes the rgb value of even pixels and stores it in an array
    for(int x = 0; x < oldSize.x; x+=2)
    {
      for(int y = 0; y < oldSize.y; y+=2)
      {
        pixelData.push_back(image.getPixel(x,y).toInteger());
      }
    }

    //iterates through the array to rebuild the image
    image.create(newSize.x, newSize.y);
    int z = 0;

    for(int x = 0; x < newSize.x; x++)
    {
      for(int y = 0; y < newSize.y; y++)
      {
        image.setPixel(x, y, sf::Color(pixelData[z]));
        z++;
      }
    }

    //recursion in case you want to scale the image multiple times
    if(size > 1)
    {
      size--;
      resizeImage(image, size);
    }
  }
  //increases the image, not adviced doing this more than 3 times
  else if(size < 0)
  {
    newSize.x = oldSize.x * 2;
    newSize.y = oldSize.y * 2;
    std::cout << "new image size: " << newSize.x << " - " << newSize.y << std::endl;
    pixelData.clear();

    //takes the rgb value of all the pixels and stores it in an array
    for(int x = 0; x < oldSize.x; x++)
    {
      for(int y = 0; y < oldSize.y; y++)
      {
        pixelData.push_back(image.getPixel(x,y).toInteger());
      }
    }

    //iterates through the array to rebuild the image
    image.create(newSize.x, newSize.y);
    int z = 0;

    for(int x = 0; x < newSize.x; x+=2)
    {
      for(int y = 0; y < newSize.y; y+=2)
      {
        image.setPixel(x, y, sf::Color(pixelData[z]));
        image.setPixel(x+1, y, sf::Color(pixelData[z]));
        image.setPixel(x, y+1, sf::Color(pixelData[z]));
        image.setPixel(x+1, y+1, sf::Color(pixelData[z]));
        z++;
      }
    }

    //recursion in case you want to scale the image multiple times
    size++;
    resizeImage(image, size);
  }
  else
  {
    std::cout << "No changes to the image!" << std::endl;
  }
}
