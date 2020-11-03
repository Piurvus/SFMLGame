#include "Menu.hpp"

Menu::Menu(std::shared_ptr<Context> &m_context) :
    context(m_context), playIsSelected(true), playIsClicked(false),
    exitIsSelected(false), exitIsClicked(false)
{

}

Menu::~Menu() {

}

void Menu::init()
{
    //  add and set fonts
} 
void Menu::update(sf::Time deltaTime)
{
    if (playIsSelected)
    {

    }
    else if (exitIsSelected)
    {

    }
    if (playIsClicked)
    {

    }
    else if (exitIsClicked)
    {

    }
} 
void Menu::render()
{
    context->m_window->clear({200, 200, 200, 0});
    //  m_context->m_window->draw()
    context->m_window->display();
} 
void Menu::processInput()
{
    sf::Event event;

    while(context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            context->m_window->close();
        else if (event.type == sf::Event::KeyPressed)
        {
            switch(event.key.code)
            {
                case sf::Keyboard::Up:
                {
                    playIsSelected = true;
                    playIsClicked = false;
                    break;
                }
                case sf::Keyboard::Down:
                {
                    exitIsSelected = true;
                    exitIsClicked = false;
                    break;

                }
                case sf::Keyboard::Return:
                {
                    if (playIsSelected)
                        playIsClicked = true;
                    if (exitIsSelected)
                        exitIsClicked = true;
                    break;
                }
                default:
                {
                    
                }
            }
        }
    }


} 

