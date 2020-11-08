#include "Player.h"


m_Entity::Player::~Player()
{
}

void m_Entity::Player::render()
{
    m_context->m_window->clear({ 200, 200, 200, 0 });
    //  m_m_context->m_window->draw()

    m_context->m_window->display();
}
void m_Entity::Player::update(sf::Time deltaTime, std::queue<unsigned int>& keys)
{
}

