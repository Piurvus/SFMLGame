#pragma once

#include "State.hpp"
#include "StateMan.hpp"
#include "Menu.hpp"

struct Context
{
    std::unique_ptr<sf::RenderWindow> m_window;
    std::unique_ptr<Engine::StateMan> m_states;
    //  assets

    Context()
    {
        m_window = std::make_unique<sf::RenderWindow>();
        m_states = std::make_unique<Engine::StateMan>();
    }
};

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