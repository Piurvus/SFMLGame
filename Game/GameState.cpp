#include "GameState.h"

GameState::GameState(std::shared_ptr<Context>& m_context):
	m_context(m_context)
{
}

GameState::~GameState()
{
}

void GameState::init()
{
}

void GameState::update(sf::Time deltaTime)
{
}

void GameState::processInput()
{
}

void GameState::render()
{
	m_context->m_window->clear({ 200, 200, 200, 0 });
	m_context->m_window->display();
}
