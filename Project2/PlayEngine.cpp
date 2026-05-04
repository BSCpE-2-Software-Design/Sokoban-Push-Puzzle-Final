#include "PlayEngine.h"

PlayEngine::PlayEngine(SFML_AssetManager* assetPtr)
    : level(10, 10), assets(assetPtr), moves(0) {

    // Mag-loop para lagyan ng pader (ID 1) ang paligid ng 10x10 grid
    for (int i = 0; i < 10; i++) {
        level.setTile(i, 0, 1);    // Taas
        level.setTile(i, 9, 1);    // Ibaba
        level.setTile(0, i, 1);    // Kaliwa
        level.setTile(9, i, 1);    // Kanang
        

    }
    //  mga pader sa loob para sa puzzle layout
    level.setTile(4, 4, 3);
    //level.setTile(3, 3, 1);
    //level.setTile(3, 4, 1);
   //level.setTile(3, 5, 1);
   // level.setTile(6, 6, 1);
   // level.setTile(6, 7, 1);
   // level.setTile(3, 9, 1);

    playerX = 1;
    playerY = 1;
    level.setTile(playerX, playerY, 2); // Player naman ay ID 2
}
// Function para sa paggalaw base sa grid
void PlayEngine::processMove(int dx, int dy) {
    int nextX = playerX + dx;
    int nextY = playerY + dy;
    int tileAtNext = level.getTile(nextX, nextY);

    // 1. Kung Wall, wag kumilos
    if (tileAtNext == 1) return;

    // 2. Kung Box (ID 3), tinutulak na box
    if (tileAtNext == 3) {
        int behindBoxX = nextX + dx;
        int behindBoxY = nextY + dy;

        // Pwede lang itulak kung ang likod ng box ay Empty Space (ID 0)
        if (level.getTile(behindBoxX, behindBoxY) == 0) {
            level.setTile(behindBoxX, behindBoxY, 3); // Ilipat ang Box sa bagong pwesto
            level.setTile(nextX, nextY, 0);           // Gawing empty ang pinanggalingan ng box
        }
        else {
            return; // Hindi maitulak ang box dahil may harang sa likod
        }
    }

    // 3.Player Position sa Grid
    level.setTile(playerX, playerY, 0); 
    playerX = nextX;
    playerY = nextY;
    level.setTile(playerX, playerY, 2); 
}
// Function para sa Keyboard Inputs

void PlayEngine::handleInput(const sf::Event& event) {
    // I-check kung KeyPressed ang event
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::W) processMove(0, -1);
        if (keyPressed->code == sf::Keyboard::Key::S) processMove(0, 1);
        if (keyPressed->code == sf::Keyboard::Key::A) processMove(-1, 0);
        if (keyPressed->code == sf::Keyboard::Key::D) processMove(1, 0);
    }
}

void PlayEngine::draw(sf::RenderWindow& window) {
    // 1. Kunin ang texture mula sa manager
    sf::Sprite wallSprite(assets->getTexture("wall"));

    // 2.  64x64 pixels ang brick
    sf::Vector2u size = assets->getTexture("wall").getSize();
    wallSprite.setScale({ 64.0f / size.x, 64.0f / size.y });

    // 3. loop ng buong grid
    for (int y = 0; y < level.getHeight(); y++) {
        for (int x = 0; x < level.getWidth(); x++) {

            // 1. Wall Logic (ID 1)
            if (level.getTile(x, y) == 1) {
                wallSprite.setPosition({ x * 64.f, y * 64.f });
                window.draw(wallSprite);
            }

            // 2. Box Logic (ID 3) - 
            else if (level.getTile(x, y) == 3) {
                sf::RectangleShape box({ 56.f, 56.f });
                box.setFillColor(sf::Color::Green);
                box.setPosition({ (x * 64.f) + 4.f, (y * 64.f) + 4.f });
                window.draw(box);
            }

            // 3. Player Logic (ID 2)
            else if (level.getTile(x, y) == 2) {
                sf::CircleShape player(32.f);
                player.setFillColor(sf::Color::Red);
                player.setPosition({ x * 64.f, y * 64.f });
                window.draw(player);
            }
        }
    
        
    }

}