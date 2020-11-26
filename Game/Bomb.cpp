#include "Bomb.h"

Bomb::Bomb(std::shared_ptr<Context> context, std::shared_ptr<sf::Vector2f> poss, unsigned int squaresize, sf::Vector2f pos, unsigned int strength) :
    Entity(context, poss, 100), left(false), right(false), up(false), down(false), speed(10.f), squaresize(squaresize), position(sf::RectangleShape()),
    strength(strength)
{
    position.setSize({ static_cast<float>(squaresize), static_cast<float>(squaresize) });
    position.setPosition({ pos });
}

Bomb::~Bomb()
{
}

void Bomb::getHit(int dir)
{
    //  have to implement a stop mechanism i guess ,o,  right left, down up
    switch (dir)
    {
    case 0:
        right = true;
        left = false;
        up = false;
        down = false;
        break;
    case 1:
        right = false;
        left = true;
        up = false;
        down = false;
        break;
    case 2:
        right = false;
        left = false;
        up = false;
        down = true;
    case 3: 
        right = false;
        left = false;
        up = true;
        down = false;
        break;
    default:
        right = true;
        up = true;
    }
}


void Bomb::update(sf::Time deltaTime)
{
    //  collision with player and other bombs or walls?
    if (up)
    {
        this->position.move({ 0, -speed });
    }
    else if (down)
    {
        this->position.move({ 0, speed });
    }
    else if (right)
    {
        this->position.move({ speed, 0 });
    }
    else if (left)
    {
        this->position.move({ -speed, 0 });
    }
    if (health >= 0)
        health--;
}

void Bomb::update(sf::Time deltaTime, std::shared_ptr<std::vector<std::vector<int>>> m_Field)
{
    //  save old position

    update(deltaTime);

    //  delete old position in field and add the new

}

const sf::Vector2i Bomb::getPos() const
{
    return {static_cast<int>(this->position.getGlobalBounds().top/squaresize), static_cast<int>(this->position.getGlobalBounds().left/squaresize)};
}

const int Bomb::getStrength() const
{
    return strength;
}

void Bomb::render()
{
    if (health > 80)
        this->position.setFillColor({ 150, 100, 100 });
    else if (health > 60)
        this->position.setFillColor({ 200, 100, 100 });
    else if (health > 40)
        this->position.setFillColor({ 220, 120, 120 });
    else if (health > 20)
        this->position.setFillColor({ 240, 150, 150 });
    else
        this->position.setFillColor({ 255, 180, 180 });
   

    this->m_context->m_window->draw(this->position);
}

bool Bomb::goesBoom() const
{
    return health <= 0;
}

void Bomb::goBoom()
{
    health = 0;
}
