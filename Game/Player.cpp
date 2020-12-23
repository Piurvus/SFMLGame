#include "Player.h"
#include <iostream>


void m_Entity::Player::init()
{
    sf::Sprite s1;
    sf::Sprite s2;
    sf::Sprite s3;
    sf::Sprite s4;
    s1.setTexture(m_context->m_assets->getTexture(PWALK1));
    s2.setTexture(m_context->m_assets->getTexture(PWALK2));
    s3.setTexture(m_context->m_assets->getTexture(PWALK3));
    s4.setTexture(m_context->m_assets->getTexture(PWALK4));
    s1.setScale({ 1.5, 1.5 });
    s2.setScale({ 1.5, 1.5 });
    s3.setScale({ 1.5, 1.5 });
    s4.setScale({ 1.5, 1.5 });
    m_Sprites.push_back(s1);
    m_Sprites.push_back(s2);
    m_Sprites.push_back(s3);
    m_Sprites.push_back(s4);
}

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
        //this->pos->setFillColor({ 0, 50, 150 });
        //m_context->m_window->draw(*pos);
        m_Sprites[static_cast<int>(this->index)].setPosition({this->getPos().y, this->getPos().x});
        m_context->m_window->draw(m_Sprites[static_cast<int>(this->index)]);
    }
}




void m_Entity::Player::update(sf::Time deltaTime)
{
    //  hier evtl ins field zurück runden?
    float x = this->getPos().y;
    float newx = round(x / square) * square;

    float y = this->getPos().x;

    float newy = round(y / square) * square;

    if (up || left || right || down)
    {
        if (this->index <= 3.9f)
            this->index += 0.1f;
        else
            this->index = 0.0f;
    }


    if (up)
    {
        this->pos->move({ newx - x, -speed });
	}
    if (down)
    {
        this->pos->move({ newx-x, speed });
    }
    if (left)
    {
        this->pos->move({ -speed, newy-y });
    }
    if (right)
    {
        this->pos->move({ speed, newy-y });
    }
}
void m_Entity::Player::update(sf::Time deltaTime, std::shared_ptr<std::queue<unsigned int>> keys, std::vector<std::vector<int>> &field, unsigned int square)
{
    this->square = square;
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
		
        else if (field[static_cast<unsigned int>(position.y - 1)][static_cast<unsigned int>(position.x + 0.25 * square)] || 
            field[static_cast<unsigned int>(position.y - 1)][static_cast<unsigned int>(position.x + 0.75 * square)])
        {
            if (position.y - square < 1 || position.x + square >= field[0].size())
                up = false;
            else if (field[static_cast<unsigned int>(position.y - square - 1)][static_cast<unsigned int>(position.x + 0.25 * square)] ||
                field[static_cast<unsigned int>(position.y - square - 1)][static_cast<unsigned int>(position.x + 0.75 * square)])
                up = false;
            //  Bomb collision
            if (field[static_cast<unsigned int>(position.y - 1)][static_cast<unsigned int>(position.x + 0.25 * square)] == 50 ||
                field[static_cast<unsigned int>(position.y - 1)][static_cast<unsigned int>(position.x + 0.75 * square)] == 50)
            {
                hitbomb = 4;
                this->setPosition({ -1, round(position.y / square) * square });
            }
            else
                up = false;

        }
    }

    //  bug somewhere
    if (down)
    {
        if(position.y+square >= field.size()-1 || position.x + square >= field[0].size())
            down = false;
		
        else if (field[static_cast<unsigned int>(position.y+square + 1)][static_cast<unsigned int>(position.x + 0.25 * square)] || 
            field[static_cast<unsigned int>(position.y+square + 1)][static_cast<unsigned int>(position.x + 0.75 * square)])
        {
            if (position.y + 2 * square >= field.size() - 1 || position.x + square >= field[0].size())
                down = false;
            else if (field[static_cast<unsigned int>(position.y + 2*square + 1)][static_cast<unsigned int>(position.x + 0.25 * square)] ||
                field[static_cast<unsigned int>(position.y + 2*square + 1)][static_cast<unsigned int>(position.x + 0.75 * square)])
                down = false;

            //  Bomb collision
            if (field[static_cast<unsigned int>(position.y + square + 1)][static_cast<unsigned int>(position.x + 0.25 * square)] == 50 ||
                field[static_cast<unsigned int>(position.y + square + 1)][static_cast<unsigned int>(position.x + 0.75 * square)] == 50)
            {
                hitbomb = 3;
                //this->setPosition({ -1, round(position.y / square) * square });
            }
            else
                down = false;
        }
    }

    if (left)
    {
		 if(position.x < 1 || position.y + square >= field.size())
            left = false;
		

        else if (field[static_cast<unsigned int>(position.y + 0.25*square)][static_cast<unsigned int>(position.x - 1)] || 
            field[static_cast<unsigned int>(position.y + 0.75 * square)][static_cast<unsigned int>(position.x - 1)])
        {
             if (position.x - square < 1 || position.y + square >= field.size())
                 left = false;
             else if (field[static_cast<unsigned int>(position.y + 0.25 * square)][static_cast<unsigned int>(position.x-square - 1)]||
                 field[static_cast<unsigned int>(position.y + 0.75 * square)][static_cast<unsigned int>(position.x-square - 1)])
                 left = false;

            //  Bomb collision
             if (field[static_cast<unsigned int>(position.y + 0.25 * square)][static_cast<unsigned int>(position.x - 1)] == 50 ||
                 field[static_cast<unsigned int>(position.y + 0.75 * square)][static_cast<unsigned int>(position.x - 1)] == 50)
             {
                 hitbomb = 2;
                this->setPosition({ round(position.x / square) * square, -1 });
             }
            else
                left = false;
        }
    }

    //bug somewhere
	if (right)
		{
            if(position.y+square >= field.size()-1 || position.x + square >= field[0].size())
				right = false;
			
			else if (field[static_cast<unsigned int>(position.y + 0.25*square)][static_cast<unsigned int>(position.x + square + 1)] || 
                field[static_cast<unsigned int>(position.y + 0.75 * square)][static_cast<unsigned int>(position.x + square + 1)])
			{
                if (position.y + square >= field.size() - 1 || position.x + 2 * square >= field[0].size())
                        right = false;
                else if (field[static_cast<unsigned int>(position.y + 0.25 * square)][static_cast<unsigned int>(position.x + 2 * square + 1)] ||
                        field[static_cast<unsigned int>(position.y + 0.75 * square)][static_cast<unsigned int>(position.x + 2 * square + 1)])
                        right = false;

                //  Bomb collision
                if (field[static_cast<unsigned int>(position.y + 0.25 * square)][static_cast<unsigned int>(position.x + square + 1)] == 50 ||
                    field[static_cast<unsigned int>(position.y + 0.75 * square)][static_cast<unsigned int>(position.x + square + 1)] == 50)
                {
                    hitbomb = 1;
                    //this->setPosition({ round(position.x / square) * square, -1 });
                }
                else
                    right = false;


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

const int m_Entity::Player::hitBomb()
{
    int buf = hitbomb;
    hitbomb = 0;
    return buf;
}

void m_Entity::Player::setPosition(sf::Vector2f p)
{  
    sf::Transform matrix = this->pos->getTransform();

    auto position = matrix.transformPoint(this->pos->getPoint(0));

    if (p.y == -1)
        this->pos->move({ p.x - position.x, 0 });
    else if (p.x == -1)
        this->pos->move({ 0, p.y - position.y });
    else
        this->pos->move({ p.x - position.x, p.y - position.y });
}

