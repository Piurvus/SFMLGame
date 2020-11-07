#pragma once
#include "Entity.h"
#include <queue>

namespace m_Entity
{
	class Player : public Entity
	{
	private:
		std::queue<unsigned int> *keys;

	public:
		Player(Context& m_context, sf::Vector2f& pos) :Entity(m_context, pos, 100) {};
		~Player();

		void render();
		void update(sf::Time deltaTime, std::queue<unsigned int>& keys);

	};
}
