#include "Game.hpp"


//  INIT FUNCTIONS

void Game::InitWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(200, 200), "SFML works!");
}


//  CONSTRUCTOR/DESTRUCTOR

Game::Game() 
{
    this->InitWindow();       
}

Game::~Game() 
{
    delete window;
}


//  GAME FLOW

void Game::updateEvents()
    {
    while (this->window->pollEvent(this->event))
            {
                if (this->event.type == sf::Event::Closed)
                    this->window->close();
            }

}
void Game::run()
{
    while (this->window->isOpen())
    {
        this->update();
        this->render();
    }
}
void Game::update()
{
    this->updateEvents();
}
void Game::render()
{
    this->window->clear();

    // additional magic

    this->window->display();

}
