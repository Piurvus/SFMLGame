#pragma once

#include "StateMan.hpp"
#include "Menu.hpp"
#include "Helper.hpp"

class Game {

private:
    //  Variables

    std::shared_ptr<Context> m_context;

    const sf::Time TIME_PER_FRAME = sf::seconds(1.f/60.f);


    //  Init
    void InitWindow();


public:
    Game();
    virtual ~Game();

    //  Game flow
    void run();
};