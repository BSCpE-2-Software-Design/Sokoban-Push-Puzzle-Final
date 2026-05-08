#include "PlayEngine.h"

PlayEngine::PlayEngine(SFML_AssetManager* assetPtr)
    : level(15, 15), assets(assetPtr), moves(0) {

    // Mag-loop para lagyan ng pader (ID 1) ang paligid ng 15x15 grid
    for (int i = 0; i < 15; i++) {
        level.setTile(i, 0, 1);    // Taas
        level.setTile(i, 14, 1);    // Ibaba
        level.setTile(0, i, 1);    // Kaliwa
        level.setTile(14, i, 1);    // Kanang
        

    }
    //  mga pader sa loob para sa puzzle layout
    // level.setTile(x,y,1)
	// x - horizontal, y - vertical
    level.setTile(4, 4, 3);
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
    level.setTile(10, 12, 1);
    level.setTile(10, 5, 1);


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
    moves++;
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
    //  Kunin ang texture mula sa manager
    sf::Sprite wallSprite(assets->getTexture("wall"));

    //  64x64 pixels ang brick
    sf::Vector2u size = assets->getTexture("wall").getSize();
    wallSprite.setScale({ 64.0f / size.x, 64.0f / size.y });

    //  loop ng buong grid
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

            // 3. Player Logic (ID 2
            else if (level.getTile(x, y) == 2) {
                sf::CircleShape player(32.f);
                player.setFillColor(sf::Color::Red);
                player.setPosition({ x * 64.f, y * 64.f });
                window.draw(player);
            }

            else if (level.getTile(x, y) == 4) {
                sf::CircleShape goal(12.f);
                goal.setFillColor(sf::Color(255, 192, 203));
               
				goal.setPosition({ (x * 64.f) + 20.0f, y * 64.f + 20.0f });
                window.draw(goal);

            }
        }
    
        
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
        level.setTile(4, 4, 3); // Box
        level.setTile(playerX, playerY, 2);// Player
        level.setTile(4, 4, 3);
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
        level.setTile(10, 12, 1);
        level.setTile(10, 5, 1);
        level.setTile(10,10, 4); 
        // Magdagdag pa ng ibang pader o tiles dito kung meron ka sa constructor
    


}
bool PlayEngine::checkWin() {
    if(level.getTile(10, 10) == 3 && level.getTile(11, 10) == 3) {
        return true;
	}
    
    return false;
}
