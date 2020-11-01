#pragma once

#include <State.hpp>

class Game {

private:

    //  Variables
    sf::RenderWindow *window;
    sf::Event event;
    sf::Clock clock;

    float deltatime;


    //  Init
    void InitWindow();


public:
    Game();
    virtual ~Game();

    //  Game flow
    void updateDt();
    void updateEvents();
    void run();
    void update();
    void render();
};