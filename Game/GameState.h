#pragma once
#include "State.hpp"
#include "Helper.hpp"

class GameState : public Engine::State
{
private:
	//	objects fonts etc..

public:
	GameState(std::shared_ptr<Context>& m_context);
	~GameState();

	void init();
	void update(sf::Time deltaTime);
	void processInput();
	void render();



};
