#include "Player.h"


m_Entity::Player::~Player()
{
}

void m_Entity::Player::render()
{
    //  m_context->m_window->draw()
    m_context->m_window->draw(*pos);
}




void m_Entity::Player::update(sf::Time deltaTime)
{
}
void m_Entity::Player::update(sf::Time deltaTime, std::shared_ptr<std::queue<unsigned int>> keys)
{
    this->keys = std::move(keys);
    while (!this->keys->empty())
    {
        int k = this->keys->front();
        switch (k)
        {
        case sf::Keyboard::Right:
            this->pos->move({ 10, 0 });
            break;
        case sf::Keyboard::Left:
            this->pos->move({ -10, 0 });
            break;
        case sf::Keyboard::Up:
            this->pos->move({ 0, -10 });
            break;
        case sf::Keyboard::Down:
            this->pos->move({ 0, 10 });
            break;
        default:
            break;

        }
        this->keys->pop();
    }
}

