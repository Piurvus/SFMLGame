#include "Player.h"


m_Entity::Player::~Player()
{
}

void m_Entity::Player::render()
{
    //  m_context->m_window->draw()
    this->pos->setFillColor({ 0, 50, 150 });
    m_context->m_window->draw(*pos);
}




void m_Entity::Player::update(sf::Time deltaTime)
{
    if (up)
        this->pos->move({ 0, -speed });
    if (down)
        this->pos->move({ 0, speed });
    if (left)
        this->pos->move({ -speed, 0 });
    if (right)
        this->pos->move({ speed,0 });
}
void m_Entity::Player::update(sf::Time deltaTime, std::shared_ptr<std::queue<unsigned int>> keys, std::shared_ptr<std::vector<std::vector<int>>> field)
{
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
        default:
            down = false;
            up = false;
            left = false;
            right = false;
            break;
        }
        this->keys->pop();
    }

    //  check field
    unsigned int square = m_context->m_window->getSize().y / field->size();

    sf::Transform matrix = this->pos->getTransform();

    auto position = matrix.transformPoint(this->pos->getPoint(0));
    float diffX = static_cast<int>(position.x) % square /100.f;
    float diffY = static_cast<int>(position.y) % square /100.f;


    if (down && position.y/square +1 >= field->size())
    {
        down = false;
    }
    if (up && position.y / square == 0)
    {
        up = false;
    }
    if (left && position.x / square == 0)
    {
        left = false;
    }
    if (right && position.x / square + 1 > field->begin()->size())
    {
        right = false;
    }
    if (down && *((field->begin() + (static_cast<int>(position.y / square )+1))->begin()+ (static_cast<int>(position.x / square))) == 1)
    {
        down = false;
    }

   
    if (up || down)
    {
        if (diffX < 0.5 && diffX > 0.1)
        {
            this->pos->move({ -speed, 0 });
        }
        else if (diffX >= 0.5 && diffX < 0.9)
        {
            this->pos->move({ speed, 0 });
        }
    }
    if (left || right)
    {
        if (diffY < 0.5 && diffY > 0.1)
        {
            this->pos->move({ 0, -speed});
        }
        else if (diffY >= 0.5 && diffY < 0.9)
        {
            this->pos->move({ 0, speed });
        }

    }

    update(deltaTime);
}

