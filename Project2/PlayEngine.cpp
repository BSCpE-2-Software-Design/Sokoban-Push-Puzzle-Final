
#include "PlayEngine.h"
#include <iostream>

PlayEngine::PlayEngine(SFML_AssetManager* assetPtr)
    : level(15,15), assets(assetPtr), moves(0), winText(font)
{ 
    reset(1);
    
    if (font.openFromFile("arial.ttf")) {
        winText.setString("WINNER!!!");
        winText.setFont(font);
        winText.setCharacterSize(100);
        winText.setFillColor(sf::Color::Yellow);
        winText.setPosition({ 250.f, 400.f });
    }

} 



// Function para sa paggalaw base sa grid
void PlayEngine::processMove(int dx, int dy) {
    int nextX = playerX + dx;
    int nextY = playerY + dy;

    int targetTile = level.getTile(nextX, nextY);

    // 1. Kung Wall, huwag gumalaw
    if (targetTile == 1) return;

    // 2. Kung Box (ID 3)
    if (targetTile == 3) { // Kung Box ang tinutulak
        int behindBoxX = nextX + dx;
        int behindBoxY = nextY + dy;
        int behindTile = level.getTile(behindBoxX, behindBoxY);

        if (behindTile == 0 || behindTile == 4) {
            level.setTile(behindBoxX, behindBoxY, 3); 


            if (currentLevel == 1) {
                
                if (nextX == 12 && nextY == 10) {
                    level.setTile(nextX, nextY, 4);
                }
                
                else if (level.getTile(nextX, nextY) == 3) {
                    level.setTile(nextX, nextY, 0);
                }
            }
            else if (currentLevel == 2) {
                if (nextX == 12 && nextY == 1) {
                    level.setTile(nextX, nextY, 4);
                }
                else if (level.getTile(nextX, nextY) == 3) {
                    level.setTile(nextX, nextY, 0);
                }
            }

        }
        else {
            return;
        }
    }
    if (level.getTile(playerX, playerY) == 2) {
        if (currentLevel == 1 && playerX == 12 && playerY == 10) {
            level.setTile(playerX, playerY, 4); 
        }
        else if (currentLevel == 2 && playerX == 12 && playerY == 1) {
            level.setTile(playerX, playerY, 4);
        }
        else {
            level.setTile(playerX, playerY, 0); 
        }
    }

   
    playerX = nextX;
    playerY = nextY;
    level.setTile(playerX, playerY, 2); 
}


void PlayEngine::handleInput(const sf::Event& event) {
   
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::W) processMove(0, -1);
        if (keyPressed->code == sf::Keyboard::Key::S) processMove(0, 1);
        if (keyPressed->code == sf::Keyboard::Key::A) processMove(-1, 0);
        if (keyPressed->code == sf::Keyboard::Key::D) processMove(1, 0);
    }
}

void PlayEngine::Draw(sf::RenderWindow& window) {

    sf::Sprite wallSprite(assets->getTexture("wall"));
    wallSprite.setTextureRect({ {0, 0}, {64, 64} });
    // 2. Loop ng buong grid
    for (int y = 0; y < level.getHeight(); y++) {
        for (int x = 0; x < level.getWidth(); x++) {

            int tileID = level.getTile(x, y);

            if (tileID == 1) {
                wallSprite.setPosition({ x * 64.f, y * 64.f });
                window.draw(wallSprite);
            }
            
            else if (tileID == 4) {
                sf::RectangleShape goal({ 24.f, 24.f }); // Maliit na square lang para sahig
                goal.setFillColor(sf::Color::Yellow);    // Kulay dilaw ang goal indicator
                
                goal.setPosition({ (x * 64.f) + 20.f, (y * 64.f) + 20.f });
                window.draw(goal);
            }
            else if (tileID == 3) {
                sf::RectangleShape box({ 56.f, 56.f });
                box.setFillColor(sf::Color::Green);
                box.setPosition({ (x * 64.f) + 4.f, (y * 64.f) + 4.f });
                window.draw(box);
            }
            else if (tileID == 2) {
                sf::CircleShape player(28.f);
                player.setFillColor(sf::Color::Red);
                player.setPosition({ (x * 64.f) + 4.f, (y * 64.f) + 4.f });
                window.draw(player);
            }
        }
    }

  
}
void PlayEngine::reset(int levelNum) {
    currentLevel = levelNum;
    playerX = 1;
    playerY = 1;
    moves = 0;

    // I-clear ang grid (Gawing 0/Empty lahat muna)
    for (int y = 0; y < level.getHeight(); y++) {
        for (int x = 0; x < level.getWidth(); x++) {
            level.setTile(x, y, 0);
        }
    }

	//set up ng pader or bakod sa paligid ng grid
    for (int i = 0; i < 15; i++) {
        level.setTile(i, 0, 1);    // Taas
        level.setTile(i, 14, 1);   // Ibaba
        level.setTile(0, i, 1);    // Kaliwa
        level.setTile(14, i, 1);   // Kanang
    }

    //   objects at player
    if (currentLevel == 1) {
        playerX = 1;
        playerY = 1;
        level.setTile(playerX, playerY, 2); // Player naman ay ID 2

        level.setTile(4, 4, 3); //box
        level.setTile(12, 10, 4); //goal

        level.setTile(2, 6, 1);
        level.setTile(2, 8, 1);
        level.setTile(2, 10, 1);
        level.setTile(3, 3, 1);
        level.setTile(3, 4, 1);
        level.setTile(3, 5, 1);
        level.setTile(3, 6, 1);
        level.setTile(3, 7, 1);
        level.setTile(3, 8, 1);
        level.setTile(3, 9, 1);
        level.setTile(3, 10, 1);
        level.setTile(3, 11, 1);
        level.setTile(3, 12, 1);
        level.setTile(11, 13, 1);
        level.setTile(7, 7, 1);
        level.setTile(8, 7, 1);
        level.setTile(9, 7, 1);
        level.setTile(10, 7, 1);
        level.setTile(11, 7, 1);
        level.setTile(12, 7, 1);
        level.setTile(13, 7, 1);
        level.setTile(6, 4, 1);
        level.setTile(5, 4, 1);
        level.setTile(7, 4, 1);
        level.setTile(8, 4, 1);
        level.setTile(9, 4, 1);
        level.setTile(10, 4, 1);
        level.setTile(11, 4, 1);
        level.setTile(6, 10, 1);
        level.setTile(7, 10, 1);
        level.setTile(8, 10, 1);
        level.setTile(9, 10, 1);
        level.setTile(10, 10, 1);
        level.setTile(11, 10, 1);
        level.setTile(11, 8, 1);
        level.setTile(10, 5, 1);
        level.setTile(11, 12, 1);
        //level.setTile(12, 12, 4);
       
    }
    else if (currentLevel == 2) {
		// new level for level 2, same format lang pero iba ang layout ng walls, box, at goal
        playerX = 2; playerY = 2;
        level.setTile(playerX, playerY, 2);
        level.setTile(2, 12, 3); //box
		level.setTile(12, 1, 4); //goal
      

        level.setTile(1, 2, 1);
        level.setTile(3, 2, 1);
        level.setTile(4, 2, 1);
        level.setTile(5, 2, 1);
        level.setTile(6, 3, 1);
        level.setTile(7, 4, 1);
        level.setTile(8, 5, 1);
        level.setTile(9, 6, 1);
        level.setTile(10, 7, 1);
        level.setTile(11, 8, 1);
        level.setTile(13, 13, 1);
        level.setTile(13, 12, 1);
        level.setTile(13, 11, 1);
        level.setTile(12, 13, 1);
        level.setTile(12, 12, 1);
        level.setTile(12, 11, 1);
        level.setTile(11, 13, 1);
        level.setTile(11, 12, 1);
        level.setTile(11, 11, 1);
        level.setTile(10, 13, 1);
        level.setTile(10, 12, 1);
        level.setTile(10, 11, 1);
        level.setTile(2, 11, 1);
        level.setTile(4, 11, 1);
        level.setTile(4, 12, 1);
        level.setTile(4, 13, 1);
        level.setTile(9, 11, 1);
        level.setTile(8, 10, 1);
        level.setTile(7, 9 ,1);
        level.setTile(10, 3, 1);
        level.setTile(11, 3, 1);
        level.setTile(12, 3, 1);

       // level.setTile(2, 2, 1);
        //level.setTile(2, 3, 1);
       // level.setTile(2, 4, 1);
       /// level.setTile(2, 5, 1);
       // level.setTile(3, 3, 1);
        //level.setTile(4, 4, 1);
	}

}
bool PlayEngine::checkWin() {
    if (currentLevel == 1) {
        int tile = level.getTile(12, 10);
        return (tile == 3); 
    }
    else if (currentLevel == 2) {
        int tile = level.getTile(12, 1);
        return (tile == 3);
    }
    return false;
}