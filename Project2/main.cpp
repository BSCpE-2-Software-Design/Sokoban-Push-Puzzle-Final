#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include <iostream>
#include "PlayEngine.h"

int main() {
    // SFML 3: Ang VideoMode ay gumagamit na ng Vector2u sa loob ng curly braces
    sf::RenderWindow window(sf::VideoMode({ 960, 960 }), "Sokoban Engine");
    window.setFramerateLimit(60);

    SFML_AssetManager assets;
    assets.loadTexture("wall", "wall2.png"); // "wall" ang pangalan, "wall2.png" ang file

    PlayEngine game(&assets);

    while (window.isOpen()) {
        // SFML 3: Ang bagong paraan ng pag-poll ng events gamit ang std::optional
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }



            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::W) game.processMove(0, -1);
                if (keyPressed->code == sf::Keyboard::Key::S) game.processMove(0, 1);
                if (keyPressed->code == sf::Keyboard::Key::A) game.processMove(-1, 0);
                if (keyPressed->code == sf::Keyboard::Key::D) game.processMove(1, 0);

                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    game.reset(); // Tatawagin nito ang function para i-reset ang grid
                }
            }
        }
            window.clear();
            game.draw(window);
            window.display();
            if (game.checkWin()) {
                std::cout << "Congratulations! You won in " << std::endl;

            }
           



         
        

        
    }
}
