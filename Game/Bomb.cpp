#include "Bomb.h"

Bomb::Bomb(std::shared_ptr<Context> context, std::shared_ptr<sf::Vector2f> poss, unsigned int squaresize, sf::Vector2f pos, unsigned int strength) :
    Entity(context, poss, 100, squaresize), left(false), right(false), up(false), down(false), speed(10.f), squaresize(squaresize), position(sf::RectangleShape()),
    strength(strength), frame(0.f)
{
    position.setSize({ static_cast<float>(squaresize), static_cast<float>(squaresize) });
    position.setPosition({ pos });

    sf::Sprite s1;
    s1.setTexture(m_context->m_assets->getTexture(BOMB11));
    s1.setScale({ 0.4f,0.4f });
    m_Sprites.push_back(s1);
    
    s1.setTexture(m_context->m_assets->getTexture(BOMB12));
    s1.setScale({ 0.4f,0.4f });
    m_Sprites.push_back(s1);
    s1.setTexture(m_context->m_assets->getTexture(BOMB13));
    s1.setScale({ 0.4f,0.4f });
    m_Sprites.push_back(s1);

    s1.setTexture(m_context->m_assets->getTexture(BOMB14));
    s1.setScale({ 0.4f,0.4f });
    m_Sprites.push_back(s1);

    s1.setTexture(m_context->m_assets->getTexture(BOMB21));
    s1.setScale({ 0.4f,0.4f });
    m_Sprites.push_back(s1);

    s1.setTexture(m_context->m_assets->getTexture(BOMB22));
    s1.setScale({ 0.4f,0.4f });
    m_Sprites.push_back(s1);

    s1.setTexture(m_context->m_assets->getTexture(BOMB23));
    s1.setScale({ 0.4f,0.4f });
    m_Sprites.push_back(s1);

    s1.setTexture(m_context->m_assets->getTexture(BOMB24));
    s1.setScale({ 0.4f,0.4f });
    m_Sprites.push_back(s1);

    s1.setTexture(m_context->m_assets->getTexture(BOMB31));
    s1.setScale({ 0.4f,0.4f });
    m_Sprites.push_back(s1);

    s1.setTexture(m_context->m_assets->getTexture(BOMB32));
    s1.setScale({ 0.4f,0.4f });
    m_Sprites.push_back(s1);

    s1.setTexture(m_context->m_assets->getTexture(BOMB33));
    s1.setScale({ 0.4f,0.4f });
    m_Sprites.push_back(s1);

    s1.setTexture(m_context->m_assets->getTexture(BOMB34));
    s1.setScale({ 0.4f,0.4f });
    m_Sprites.push_back(s1);


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
    if (frame >= 3.9f)
        frame = 0.f;
    else frame += 0.1f;
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
        for (unsigned int i = 0; i < squaresize; i++)
            for (unsigned int j = 0; j < squaresize; j++)
                m_Field[poss.x*squaresize + i][poss.y*squaresize + j] = 0;
    }
    update(deltaTime);
        
    poss = this->getPos();

    if (up || down || left || right)
    {
        for (unsigned int i = 0; i < squaresize; i++)
            for (unsigned int j = 0; j < squaresize; j++)
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
    
    if (health > 66) {
        m_Sprites[static_cast<int>(frame)].setPosition({this->position.getPosition().x, this->position.getPosition().y });
        m_context->m_window->draw(m_Sprites[static_cast<int>(frame)]);
    }
    else if (health > 33) {
        m_Sprites[static_cast<int>(frame)+4].setPosition({this->position.getPosition().x, this->position.getPosition().y });
        m_context->m_window->draw(m_Sprites[static_cast<int>(frame)+4]);
    }
    else {
        m_Sprites[static_cast<int>(frame)+8].setPosition({this->position.getPosition().x, this->position.getPosition().y });
        m_context->m_window->draw(m_Sprites[static_cast<int>(frame)+8]);
    }   

}

bool Bomb::goesBoom() const
{
    return health <= 0;
}

void Bomb::goBoom()
{
    health = 0;
}
