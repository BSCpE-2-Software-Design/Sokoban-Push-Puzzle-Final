#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "PlayEngine.h"

int main() {
    // SFML 3: Ang VideoMode ay gumagamit na ng Vector2u sa loob ng curly braces
    sf::RenderWindow window(sf::VideoMode({ 640, 640 }), "Sokoban Engine");
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
            // I-pass ang event sa engine (siguraduhing updated ang PlayEngine.h)
            game.handleInput(*event);
        }

        window.clear();
        game.draw(window);
        window.display();
    }

    return 0;
}