#include "AssetManager.h"

SFML_AssetManager::SFML_AssetManager() {}

void SFML_AssetManager::loadTexture(std::string name, std::string filename) {
    sf::Texture tex;
    if (tex.loadFromFile(filename)) {
        textures[name] = tex;
    }
}

sf::Texture& SFML_AssetManager::getTexture(std::string name) {
    return textures[name];
}