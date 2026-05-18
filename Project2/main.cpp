#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include <iostream>
#include "PlayEngine.h"

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
    bool winTriggered = false;

    while (window.isOpen()) {
        // 1. EVENT LOOP
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // KONTROL PARA SA PLAYING STATE
            if (state == GameState::PLAYING) {
                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                    if (keyPressed->code == sf::Keyboard::Key::W) game.processMove(0, -1);
                    else if (keyPressed->code == sf::Keyboard::Key::S) game.processMove(0, 1);
                    else if (keyPressed->code == sf::Keyboard::Key::A) game.processMove(-1, 0);
                    else if (keyPressed->code == sf::Keyboard::Key::D) game.processMove(1, 0);
                    else if (keyPressed->code == sf::Keyboard::Key::Escape) {
                        game.reset(1);
                        winTriggered = false;
                    }
                }
            }
            // KONTROL PARA SA VICTORY STATE
            else if (state == GameState::VICTORY) {
                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                    if (keyPressed->code == sf::Keyboard::Key::Escape) {
                        game.reset(1);
                        state = GameState::PLAYING;
                        winTriggered = false;
                    }
                }
            }
        } 

        // 2. GAME LOGIC & WIN DETECTION (Nasa labas ng event loop)
        if (state == GameState::PLAYING && game.checkWin() && !winTriggered) {
            winTriggered = true;
            state = GameState::VICTORY;

            // POP-UP WINDOW
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

                            // PAGSARA NG WINDOW: Lipat na sa Level 2!
                            state = GameState::PLAYING;
                            game.reset(2);
                            winTriggered = false;
                        }
                    }

                    winWindow.clear(sf::Color::Black);
                    winWindow.draw(victoryText);
                    winWindow.display();
                }
            }
        }

        // 3. RENDERING 
        window.clear();
        game.Draw(window);
        window.display();
    }

    return 0;
}