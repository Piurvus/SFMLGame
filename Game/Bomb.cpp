#include "Bomb.h"

Bomb::Bomb(std::shared_ptr<Context> context, std::shared_ptr<sf::Vector2f> poss, unsigned int squaresize, sf::Vector2f pos, unsigned int strength) :
    Entity(context, poss, 100, squaresize), left(false), right(false), up(false), down(false), speed(10.f), squaresize(squaresize), position(sf::RectangleShape()),
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
        break;
    case 3: 
        right = false;
        left = false;
        up = true;
        down = false;
        break;
    default:
        //right = true;
        //up = true;
        break;
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

void Bomb::update(sf::Time deltaTime, std::vector<std::vector<int>> &m_Field)
{
    sf::Vector2i poss = this->getPos();

    if (right && ((poss.y + 1) * squaresize >= m_Field.size() || m_Field[poss.x * squaresize][(poss.y + 1) * squaresize]))
        right = false;
    if (down && ((poss.x + 1) * squaresize >= m_Field[0].size() || m_Field[(poss.x+1) * squaresize][poss.y * squaresize]))
        down = false;
    
    if (up && (poss.x == 0 || m_Field[poss.x * squaresize-1][poss.y *squaresize]))
    {
        if (this->position.getGlobalBounds().top >= poss.x*squaresize+speed);
        else
            up = false;
    }
    
    if (left && (poss.y == 0 || m_Field[poss.x * squaresize][poss.y *squaresize -1]))
    {
        if (this->position.getGlobalBounds().left >= poss.y*squaresize+speed);
        else
            left = false;
    }
    if (up || down || left || right)
    {
        for (int i = 0; i < squaresize; i++)
            for (int j = 0; j < squaresize; j++)
                m_Field[poss.x*squaresize + i][poss.y*squaresize + j] = 0;
    }
    update(deltaTime);
        
    poss = this->getPos();

    if (up || down || left || right)
    {
        for (int i = 0; i < squaresize; i++)
            for (int j = 0; j < squaresize; j++)
                m_Field[poss.x*squaresize+i][poss.y*squaresize + j] = 50;

    }
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
