#pragma once
#include "Helper.hpp"


class Entity
{
private:

protected:
    std::shared_ptr<Context> m_context;
	std::shared_ptr<sf::Vector2f> pos;
	unsigned int health;

public:
	Entity(std::shared_ptr<Context> context, std::shared_ptr<sf::Vector2f> poss, unsigned int health) :m_context(context), pos(poss), health(health) {};
	virtual ~Entity() { };

	virtual void update(sf::Time deltaTime) = 0;
	virtual void render() = 0;

};
