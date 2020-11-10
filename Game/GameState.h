#pragma once
#include "State.hpp"
#include "Helper.hpp"
#include "Entity.h"
#include "Player.h"

class GameState : public Engine::State
{
private:
	//	objects fonts etc..
	std::shared_ptr<Context> m_context;
	sf::Event m_event;
	std::shared_ptr<std::queue<unsigned int>> keys;
	std::unique_ptr<m_Entity::Player> m_Player;
	//std::vector<std::unique_ptr<Entity>> m_entities;

public:
	GameState(std::shared_ptr<Context>& m_context);
	~GameState();

	void init();
	void update(sf::Time deltaTime);
	void processInput();
	void render();



};
