#ifndef SFMLGAME_RESOURCEMANAGER_HPP
#define SFMLGAME_RESOURCEMANAGER_HPP
#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <unordered_map>
#include <filesystem>
#include <string>
#include <iostream>
#include <type_traits>

// Long boi
using rdi = std::filesystem::recursive_directory_iterator;

/**
 * @brief This a flyweight resource manager, stores all the game assets as
 * unique_ptr and provides a reference when called.
 */
class ResourceManager
{
 public:
  // Copy and move constructor deleted
  ResourceManager(const ResourceManager&) = delete;
  ResourceManager(ResourceManager&&)      = delete;

  /**
   * Creates an instance of the resource manager
   * @param _asset_directory recursive path to iterate from
   */
  explicit ResourceManager(std::string _asset_directory) :
    asset_directory(std::move(_asset_directory))
  {
    // Specifies folders to be loaded in here
    AssetLoader<sf::Texture>(textures, "/Sprites/");
    AssetLoader<sf::Font>(fonts, "/Fonts/");
    AssetLoader<sf::SoundBuffer>(sounds, "/Sounds/");
    AssetLoader<sf::Shader>(shaders, "/Shaders/");

    std::cout << "Loading Complete" << std::endl;
  }

  ~ResourceManager() = default;

  // Asset Getters -------------------------------------------------------------

  // Return a texture with the name specified
  sf::Texture& getTexture(const std::string& name)
  {
    return GetAssetRef<sf::Texture>(name, textures);
  }

  // Return a font with the name specified
  sf::Font& getFont(const std::string& name)
  {
    return GetAssetRef<sf::Font>(name, fonts);
  }

  // Return a sound with the name specified
  sf::SoundBuffer& getSound(const std::string& name)
  {
    return GetAssetRef<sf::SoundBuffer>(name, sounds);
  }

  // Return a shader with the name specified
  sf::Shader& getShader(const std::string& name)
  {
    return GetAssetRef<sf::Shader>(name, shaders);
  }

 private:
  // Asset Ref return ----------------------------------------------------------

  /**
   * @tparam AssetType type of data type to be returned as
   * @tparam Map type of data container being used
   * @param name name of the file without directory extension
   * @param container data container to grab the object from
   * @return reference to that asset
   */
  template<typename AssetType, typename Map>
  AssetType& GetAssetRef(const std::string& name, Map& container)
  {
    // is the specified file present inside this container?
    if (container.count(name) == 1)
    {
      // Checks if the file trying to be returned is the same type as the file
      // requested
      if (typeid(*container[name]).name() == typeid(AssetType).name())
      {
        return *container[name];
      }
    }
    // If none of that is true, return an un-initialized unique_ptr
    std::cout << "\nERROR:\n Get request for nonexistent asset\n"
              << typeid(AssetType).name() << ", name: " << name << std::endl;

    return *container["NULL"];
  }

  // Asset loader --------------------------------------------------------------

  /**
   * Loads a specified folder form the Asset path saved inside the class
   * @tparam Asset type of data type to be loaded
   * @tparam Map type of data container to be used for storing
   * @param container where the Asset will be stored
   * @param directory Name of the folder to fetch from
   */
  template<typename Asset, typename Map>
  void AssetLoader(Map& container, const std::string& directory)
  {
    // Path to fetch from
    std::string path = asset_directory + directory;
    std::string filename;

    //If the folder is non-existent throws an error and aborts loading
    try
    {
      // Iterate trough each element found in the path
      for (const auto& file : rdi(path))
      {
        // Filename is path + name
        filename = file.path().filename().string();
        // Creates a unique ptr of the current asset
        std::unique_ptr<Asset> filePtr = std::make_unique<Asset>();
        bool loaded                    = false;

        // A shader has different parameters for loading in, therefore a
        // const-expression is needed to differentiate to other assets
        if constexpr (std::is_same<sf::Shader, Asset>::value)
        {
          // loads shaders as fragment shaders
          loaded = filePtr->loadFromFile(path + filename, sf::Shader::Fragment);
        }
        else
        {
          loaded = filePtr->loadFromFile(path + filename);
        }

        // if the asset has been loaded correctly, change the ownership
        // of the unique ptr owning the asset to the unique ptr inside the
        // provided data container
        if (loaded)
        {
          std::cout << "Loaded " + filename << std::endl;
          container[filename] = std::move(filePtr);
        }
        else
        {
          std::cout << "Failed to Load " + path << std::endl;
        }
      }
    }
    catch (std::filesystem::__cxx11::filesystem_error)
    {
      std::cout << "Folder '" << path << "' not found" << std::endl;
    }
  }

  // Fetching location
  std::string asset_directory = "NULL";
  // Asset Containers
  std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures;
  std::unordered_map<std::string, std::unique_ptr<sf::Font>> fonts;
  std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> sounds;
  std::unordered_map<std::string, std::unique_ptr<sf::Shader>> shaders;
};


#endif // SFMLGAME_RESOURCEMANAGER_HPP
