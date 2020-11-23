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
	Entity(std::shared_ptr<Context> context, std::shared_ptr<sf::Vector2f> poss, unsigned int health) :m_context(context), pos(std::make_unique<sf::RectangleShape>(*poss)), health(health) {};
	virtual ~Entity(){};

	virtual void update(sf::Time deltaTime) = 0;
	virtual void render() = 0;

	const sf::Vector2i getPos(int squaresize) const
	{ return { static_cast<int>(this->pos->getGlobalBounds().top / squaresize), static_cast<int>(this->pos->getGlobalBounds().left / squaresize) }; };

};
