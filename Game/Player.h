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
		unsigned int square;
		int hitbomb;
		std::vector<sf::Sprite> m_Sprites;
		float index;
		bool preright, preleft;

		void init();

	public:
		Player(std::shared_ptr<Context> m_context, std::shared_ptr<sf::Vector2f> pos, unsigned int squaresize) : 
			Entity(m_context, pos, 100, squaresize), keys(nullptr), left(false), right(false),
			up(false), down(false), speed(10.f), bomb(false), bombs(999), dead(false), square(0),
			hitbomb(0), index(0.0f), preright(true), preleft(false) {
			init();
		};
		//	really confused why is this even needed???? buggy code lol
		Player(std::shared_ptr<Context> m_context, std::shared_ptr<sf::Vector2f> pos) :
			Player(m_context, pos, 100) {};
		~Player();

		const bool putBomb();
		void render();
		void update(sf::Time deltaTime);
		void update(sf::Time deltaTime, std::shared_ptr<std::queue<unsigned int>> keys, std::vector<std::vector<int>>& field, unsigned int square);
		void kill();
		const bool isDead() const;
		const int hitBomb();
		void setPosition(sf::Vector2f p);
	};
};
