#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class SFML_AssetManager {
private:
    std::map<std::string, sf::Texture> textures;

public:
    SFML_AssetManager();
    void loadTexture(std::string name, std::string filename);
    sf::Texture& getTexture(std::string name);
};

#endif