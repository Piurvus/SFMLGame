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
    if (up)
		this->pos->move({ 0, -10 });
    if (down)
		this->pos->move({ 0, 10 });
    if (left)
        this->pos->move({ -10, 0 });
    if (right)
        this->pos->move({ 10,0 });

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
			right = true;
            left = false;
            up = false;
            down = false;
            break;
        case sf::Keyboard::Left:
			left = true;
            right = false;
            up = false;
            down = false;
            break;
        case sf::Keyboard::Up:
			up = true;
            down = false;
            left = false;
            right = false;
            break;
        case sf::Keyboard::Down:
			down = true;
            left = false;
            right = false;
            up = false;
            break;
        default:
            down = false;
            up = false;
            left = false;
            right = false;
            break;

        }
        this->keys->pop();
    }
    update(deltaTime);
}

