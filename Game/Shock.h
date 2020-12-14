#pragma once

#include "Entity.h"

class Shock : public Entity
{
private:
		unsigned int blue;
		sf::Vector2f position;
	public:
		Shock(std::shared_ptr<Context> context, std::shared_ptr<sf::Vector2f> poss, unsigned int health, int squaresize) :
		Entity(context, poss, health, squaresize), blue(50), position(*poss) {};
		void update(sf::Time deltaTime);
		void render();
		const bool done() const;
};
