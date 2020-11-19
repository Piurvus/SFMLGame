#pragma once
#include "Entity.h"

class Bomb : public Entity
{
private:
	bool left, right, up, down;
	float speed;

public:
	
	Bomb(std::shared_ptr<Context> context, std::shared_ptr<sf::Vector2f> poss);
	~Bomb();

	//	0 right, 1 left, 2 down, 3 up
	void getHit(int dir);

	void render();
	void update(sf::Time deltaTime);
	void update(sf::Time deltaTime, std::shared_ptr<std::vector<std::vector<int>>> m_Field);

	bool goesBoom();
};
