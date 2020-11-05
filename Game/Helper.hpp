#pragma once
#include "StateMan.hpp"
#include "AssetMan.hpp"

struct Context
{
    std::unique_ptr<sf::RenderWindow> m_window;
    std::unique_ptr<Engine::StateMan> m_states;
    std::unique_ptr<Engine::AssetMan> m_assets;
    //  assets

    Context()
    {
        m_window = std::make_unique<sf::RenderWindow>();
        m_states = std::make_unique<Engine::StateMan>();
    }
};

