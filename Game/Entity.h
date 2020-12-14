#pragma once
#include "Helper.hpp"


class Entity
{
private:

protected:
    std::shared_ptr<Context> m_context;
	std::unique_ptr<sf::RectangleShape> pos;
	int health;

public:
	Entity(std::shared_ptr<Context> context, std::shared_ptr<sf::Vector2f> poss, unsigned int health, unsigned int squaresize) :
		m_context(context), pos(std::make_unique<sf::RectangleShape>(*poss)), health(health)
	{
		this->pos->setSize({ static_cast<float>(squaresize), static_cast<float>(squaresize) });
		this->pos->setPosition({ *poss });

	};
	virtual ~Entity(){};

	virtual void update(sf::Time deltaTime) = 0;
	virtual void render() = 0;

	const sf::Vector2f getPos() const
	{ return { (this->pos->getGlobalBounds().top), (this->pos->getGlobalBounds().left) }; };
	const sf::Vector2i getPos(int square) const
	{ return { static_cast<int>(this->pos->getGlobalBounds().top/square), static_cast<int>(this->pos->getGlobalBounds().left/square) }; };


};
