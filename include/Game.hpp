#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

class Game {

private:

    //  Variables
    sf::RenderWindow *window;
    sf::Event event;


    //  Init
    void InitWindow();


public:
    Game();
    virtual ~Game();

    //  Game flow
    void updateEvents();
    void run();
    void update();
    void render();
};