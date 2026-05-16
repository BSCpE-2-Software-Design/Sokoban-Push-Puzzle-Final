
#ifndef PLAYENGINE_H
#define PLAYENGINE_H

#include "LevelModel.h"
#include "AssetManager.h"
#include <SFML/Graphics.hpp>

class PlayEngine {
private:
    SFML_AssetManager* assets;
    LevelModel level;
    int playerX, playerY;
    int moves;
    sf::Font font;
    sf::Text winText; 

public:
    PlayEngine(SFML_AssetManager* assetPtr);
    void processMove(int dx, int dy);
    void handleInput(const sf::Event& event);
    void Draw(sf::RenderWindow& window); 
    void reset();
    bool checkWin(); 
};

#endif