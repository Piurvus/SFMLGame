#pragma once
#include "Entity.h"
#include <queue>

namespace m_Entity
{
	class Player : public Entity
	{
	private:
		std::shared_ptr<std::queue<unsigned int>> keys;
		bool left, right, up, down;

	public:
		Player(std::shared_ptr<Context> m_context, std::shared_ptr<sf::Vector2f> pos) : Entity(m_context, pos, 100), keys(nullptr), left(false), right(false),
																						up(false), down(false){};
		~Player();

		void render();
		void update(sf::Time deltaTime);
		void update(sf::Time deltaTime, std::shared_ptr<std::queue<unsigned int>> keys);

	};
};
