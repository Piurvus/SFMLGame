#pragma once

#include "Entity.h"

class Block : public Entity
{
private:

	sf::Sprite sprite;

	void init();

public:


	Block(std::shared_ptr<Context> context, std::shared_ptr<sf::Vector2f> poss, unsigned int squaresize) : Entity(context, poss, 100, squaresize) 
	{
		init();
	};

	
	~Block() {};

	void update(sf::Time deltatime);

	void render();

	const int getHit() const;
};
