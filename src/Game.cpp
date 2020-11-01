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

//  update deltatime
void Game::updateDt()
{
    this->deltatime = this->clock.getElapsedTime().asSeconds();
}

//  update SFML Events
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
        this->updateDt();
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
