#include "Player.h"


m_Entity::Player::~Player()
{
}

const bool m_Entity::Player::putBomb()
{
    if (bomb && bombs)
    {
        bomb = false;
        bombs--;
        return true;
    }
    return false;
}

void m_Entity::Player::render()
{
    if (!this->isDead())
    {
        //  m_context->m_window->draw()
        this->pos->setFillColor({ 0, 50, 150 });
        m_context->m_window->draw(*pos);
    }
}




void m_Entity::Player::update(sf::Time deltaTime)
{
    //  hier evtl ins field zurück runden?
    if (up)
        this->pos->move({ 0, -speed });
    if (down)
        this->pos->move({ 0, speed });
    if (left)
        this->pos->move({ -speed, 0 });
    if (right)
        this->pos->move({ speed,0 });
}
void m_Entity::Player::update(sf::Time deltaTime, std::shared_ptr<std::queue<unsigned int>> keys, std::vector<std::vector<int>> &field, unsigned int square)
{
    if (this->isDead())
    {
        return;
    }
    //  update the key strokes
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
        case sf::Keyboard::Space:
			bomb = true;
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


    sf::Transform matrix = this->pos->getTransform();

    auto position = matrix.transformPoint(this->pos->getPoint(0));

    






    if (up)
    {
        if(position.y < 1 || position.x + square >= field[0].size())
            up = false;
		
        else if (field[position.y - 1][position.x + 0.25 * square] || field[position.y - 1][position.x + 0.75 * square])
        {
            up = false;
            if (!field[position.y - 1][position.x + 0.25 * square])
                this->pos->move({ -speed, 0 });
            else if (!field[position.y - 1][position.x + 0.75 * square])
                this->pos->move({ speed, 0 });
        }
    }
    if (down)
    {
        if(position.y+square >= field.size()-10 || position.x + square >= field[0].size())
            down = false;
		
        else if (field[position.y+square + 1][position.x + 0.25 * square] || field[position.y+square + 1][position.x + 0.75 * square])
        {
            down = false;
            if (!field[position.y+square + 1][position.x + 0.25 * square])
                this->pos->move({ -speed, 0 });
            else if (!field[position.y+ square + 1][position.x + 0.75 * square])
                this->pos->move({ speed, 0 });
        }
    }






    update(deltaTime);
}

void m_Entity::Player::kill()
{
    this->dead = true;
}

const bool m_Entity::Player::isDead() const
{
    return this->dead;
}

