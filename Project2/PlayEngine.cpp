
#include "PlayEngine.h"
#include <iostream>

PlayEngine::PlayEngine(SFML_AssetManager* assetPtr)
    : assets(assetPtr), moves(0), winText(font)
{ 

    if (font.openFromFile("arial.ttf")) {
        winText.setString("WINNER!!!");
        winText.setFont(font);
        winText.setCharacterSize(100);
        winText.setFillColor(sf::Color::Yellow);
        winText.setPosition({ 250.f, 400.f });
    }

    reset();
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
            level.setTile(behindBoxX, behindBoxY, 3); // Ilagay ang box sa target

            
            // (Dapat alam mo ang coordinates ng goals mo)
            if ((nextX == 12 && nextY == 10) || (nextX == 12 && nextY == 12)) {
                level.setTile(nextX, nextY, 4); // Ibalik ang ID 4 (Goal)
            }
            else {
                level.setTile(nextX, nextY, 0); // Gawing empty space

            }
        }
        else {
            return;
        }
    }
    // 3. I-update ang Player Position sa Grid data
    level.setTile(playerX, playerY, 0); // Gawing empty ang dating pwesto
    playerX = nextX;
    playerY = nextY;
    level.setTile(playerX, playerY, 2); // Ilagay ang player (ID 2) sa bagong pwesto
}


void PlayEngine::handleInput(const sf::Event& event) {
    // I-check kung KeyPressed ang event
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::W) processMove(0, -1);
        if (keyPressed->code == sf::Keyboard::Key::S) processMove(0, 1);
        if (keyPressed->code == sf::Keyboard::Key::A) processMove(-1, 0);
        if (keyPressed->code == sf::Keyboard::Key::D) processMove(1, 0);
    }
}

void PlayEngine::Draw(sf::RenderWindow& window) { 
    
    sf::Sprite wallSprite(assets->getTexture("wall"));

    // 2. Loop ng buong grid
    for (int y = 0; y < level.getHeight(); y++) {
        for (int x = 0; x < level.getWidth(); x++) {

            // Wall Logic (ID 1)
            if (level.getTile(x, y) == 1) {
                wallSprite.setPosition({ x * 64.f, y * 64.f });
                window.draw(wallSprite);
            }
            //box logic (ID3
            else if (level.getTile(x, y) == 3) {
                sf::RectangleShape box({ 56.f, 56.f });
                box.setFillColor(sf::Color::Green);
                box.setPosition({ (x * 64.f) + 4.f, (y * 64.f) + 4.f });
                window.draw(box);
            }

            // Player Logic (ID 2)
            else if (level.getTile(x, y) == 2) {
                sf::CircleShape player(32.f);
                player.setFillColor(sf::Color::Red);
                player.setPosition({ x * 64.f, y * 64.f });
                window.draw(player);
            }
           
        }
    }

    // 3. Win Text Logic
    if (checkWin()) {
        window.draw(winText);
    }


    
}
void PlayEngine::reset() {
    // 1. I-reset ang posisyon ng player
    playerX = 1;
    playerY = 1;

    // 2. I-reset ang counter ng moves
    moves = 0;

    // 3. I-clear ang grid (Gawing 0/Empty lahat muna)
    for (int y = 0; y < level.getHeight(); y++) {
        for (int x = 0; x < level.getWidth(); x++) {
            level.setTile(x, y, 0);
        }
    }

    // 4. I-re-setup ang mga pader/bakod (Kopyahin ang loop mo sa constructor)
    for (int i = 0; i < 15; i++) {
        level.setTile(i, 0, 1);    // Taas
        level.setTile(i, 14, 1);   // Ibaba
        level.setTile(0, i, 1);    // Kaliwa
        level.setTile(14, i, 1);   // Kanang
    }

    // 5. I-set up ulit ang objects at player
    level.setTile(4, 4, 3);
	level.setTile(playerX, playerY, 2); // Player naman ay ID 2
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
    
    //level.setTile(12, 12, 4);
    
    level.setTile(12, 10, 4);
    playerX = 1;
    playerY = 1;
    // Magdagdag pa ng ibang pader o tiles dito kung meron ka sa constructor

}
bool PlayEngine::checkWin() {
    int currentTile = level.getTile(12, 10);
    //  lalabas sa console habang naglalaro ka
    std::cout << "Current Tile at (12,10) is: " << currentTile << std::endl;

    if (currentTile == 3) { // 3 ang ID ng Box
        return true;
    }
    return false;
}