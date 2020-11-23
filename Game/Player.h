#pragma once
#include "Entity.h"
#include <queue>
#include <SFML\Graphics\Color.hpp>

namespace m_Entity
{
	class Player : public Entity
	{
	private:
		std::shared_ptr<std::queue<unsigned int>> keys;
		bool left, right, up, down;
		bool bomb;
		float speed;
		int bombs;
		bool dead;

	public:
		Player(std::shared_ptr<Context> m_context, std::shared_ptr<sf::Vector2f> pos) : Entity(m_context, pos, 100), keys(nullptr), left(false), right(false),
																						up(false), down(false), speed(10.f), bomb(false), bombs(9), dead(false){};
		~Player();

		void render();
		void update(sf::Time deltaTime);
		void update(sf::Time deltaTime, std::shared_ptr<std::queue<unsigned int>> keys, std::shared_ptr<std::vector<std::vector<int>>> m_Field);
		void kill();
		const bool isDead() const;
	};
};
