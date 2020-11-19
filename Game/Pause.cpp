#include "Pause.hpp"

Pause::Pause(std::shared_ptr<Context> context) : m_context(context), backtomenu(false), m_event(sf::Event()),
                                                 goback(false)
{
	init();
}

Pause::~Pause()
{
}

void Pause::init()
{
}

void Pause::update(sf::Time deltaTime)
{
    if (goback)
    {
        m_context->m_states->popCurrent();
    }
    if (backtomenu)
    {
        m_context->m_states->popCount(2);
    }
}

void Pause::render()
{
    m_context->m_window->clear({ 255, 255, 255 });
    m_context->m_window->display();
}

void Pause::processInput()
{
    while (m_context->m_window->pollEvent(m_event))
    {
        if (m_event.type == sf::Event::Closed)
            m_context->m_window->close();
        else if (m_event.type == sf::Event::KeyPressed)
        {
            switch (m_event.key.code)
            {
            case sf::Keyboard::Tab:
            {
                goback = true;
                backtomenu = false;
                break;
            }
            case sf::Keyboard::Escape:
            {
                goback = false;
                backtomenu = true;
                break;
            }
            }
        }
    }
     
}
