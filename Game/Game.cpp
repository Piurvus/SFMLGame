#include "Game.hpp"


//  INIT FUNCTIONS

void Game::InitWindow()
{
    //  read from file?
    m_context->m_window->create(sf::VideoMode(1000, 1000), "SFML works!");
    m_context->m_window->setFramerateLimit(120);
    m_context->m_window->setVerticalSyncEnabled(false);
}


//  CONSTRUCTOR/DESTRUCTOR

Game::Game():
    m_context(std::make_shared<Context>())
{
    this->InitWindow();     
    //  change Engine::State to a real state
    m_context->m_states->add(std::make_unique<Menu>(m_context), false);

}

Game::~Game() 
{
}


//  GAME FLOW


void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (m_context->m_window->isOpen())
    {
        timeSinceLastFrame += clock.restart();

        while(timeSinceLastFrame > TIME_PER_FRAME)
        {
            timeSinceLastFrame -= TIME_PER_FRAME;

            m_context->m_states->processStateChange();
            m_context->m_states->getCurrent()->processInput();
            m_context->m_states->getCurrent()->update(TIME_PER_FRAME);
            m_context->m_states->getCurrent()->render();
        }
    }
}
