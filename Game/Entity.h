#pragma once
#include "Helper.hpp"


class Entity
{
private:

protected:
    std::shared_ptr<Context> m_context;
	sf::Vector2f pos;
	unsigned int health;

public:
	Entity(std::shared_ptr<Context> context, sf::Vector2f& poss, unsigned int health) :m_context(context), pos(poss), health(health) {};
	virtual ~Entity() {delete& pos; delete &m_context;};

	virtual void update(sf::Time deltaTime) = 0;
	virtual void render() = 0;

};
