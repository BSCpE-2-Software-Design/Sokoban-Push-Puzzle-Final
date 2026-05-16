#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include <iostream>
#include "PlayEngine.h"

// Magdagdag ng Game State para kontrolin ang daloy ng laro
enum class GameState {
    PLAYING,
    VICTORY
};

int main() {
    sf::RenderWindow window(sf::VideoMode({ 960, 960 }), "Sokoban Engine");
    window.setFramerateLimit(60);

    SFML_AssetManager assets;
    assets.loadTexture("wall", "wall2.png");

    PlayEngine game(&assets);
    GameState state = GameState::PLAYING;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Hayaan lang gumalaw ang player KUNG nasa PLAYING state
            if (state == GameState::PLAYING) {
                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                    if (keyPressed->code == sf::Keyboard::Key::W) game.processMove(0, -1);
                    if (keyPressed->code == sf::Keyboard::Key::S) game.processMove(0, 1);
                    if (keyPressed->code == sf::Keyboard::Key::A) game.processMove(-1, 0);
                    if (keyPressed->code == sf::Keyboard::Key::D) game.processMove(1, 0);
                    if (keyPressed->code == sf::Keyboard::Key::Escape) game.reset();
                }
            }
            else if (state == GameState::VICTORY) {
                // Kung nasa Victory Screen at pinindot ang Escape, mag-reset para makalaro uli
                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                    if (keyPressed->code == sf::Keyboard::Key::Escape) {
                        game.reset();
                        state = GameState::PLAYING;
                    }
                }
            }
        }

        // I-check kung nanalo habang naglalaro
        if (state == GameState::PLAYING && game.checkWin()) {
            state = GameState::VICTORY;

            // DITO NA NATIN BUBUKSAN ANG POP-UP WINDOW
            sf::RenderWindow winWindow(sf::VideoMode({ 400, 200 }), "Victory!", sf::Style::Titlebar | sf::Style::Close);
            winWindow.setFramerateLimit(30);

            sf::Font winFont;
            if (winFont.openFromFile("arial.ttf")) {
                sf::Text victoryText(winFont);
                victoryText.setString("YOU WIN!");
                victoryText.setCharacterSize(40);
                victoryText.setFillColor(sf::Color::Green);
                victoryText.setPosition({ 110.f, 60.f });

                while (winWindow.isOpen()) {
                    while (const std::optional winEvent = winWindow.pollEvent()) {
                        if (winEvent->is<sf::Event::Closed>()) {
                            winWindow.close();
                        }
                    }
                    winWindow.clear(sf::Color::Black);
                    winWindow.draw(victoryText);
                    winWindow.display();
                }
            }
        }

        window.clear();
        game.Draw(window);
        window.display();
    }

    return 0;
}


