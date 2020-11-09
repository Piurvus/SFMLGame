#include "GameState.h"

GameState::GameState(std::shared_ptr<Context>& m_context) :
	m_context(m_context), m_event(sf::Event())
{
	init();
}

GameState::~GameState()
{
}

void GameState::init()
{
	sf::Vector2f pos = { 200.f, 200.f };
	m_entities.push_back(std::make_unique<m_Entity::Player>(m_context, pos));
}

void GameState::update(sf::Time deltaTime)
{
}

void GameState::processInput()
{
	while (m_context->m_window->pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
			m_context->m_window->close();
		else if (m_event.type == sf::Event::KeyPressed)
		{
			keys.push(m_event.key.code);
		}
	}
}

void GameState::render() 
{
	m_context->m_window->clear({ 200, 200, 200, 0 });

	//	render all entities
	for (auto it = m_entities.begin(); it != m_entities.end(); it++)
	{
		it->get()->render();
	}
	
	m_context->m_window->display();
}
