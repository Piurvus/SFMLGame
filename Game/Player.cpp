#include "Player.h"


m_Entity::Player::~Player()
{}

void m_Entity::Player::render()
{
    //  m_context->m_window->draw()
    m_context->m_window->draw(sf::RectangleShape(*pos));

}




void m_Entity::Player::update(sf::Time deltaTime)
{
}
void m_Entity::Player::update(sf::Time deltaTime, std::shared_ptr<std::queue<unsigned int>> keys)
{
    this->keys = std::move(keys);
}

