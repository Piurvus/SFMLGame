#include "GameState.h"

GameState::GameState(std::shared_ptr<Context>& m_context) :
	m_context(m_context), m_event(sf::Event()), keys(std::make_shared<std::queue<unsigned int>>()), m_Player(nullptr)
{
	init();
}

GameState::~GameState()
{
}

void GameState::init()
{
	std::shared_ptr<sf::Vector2f> pos = std::move(std::make_shared<sf::Vector2f>( 200.f, 200.f ));
	m_Player = std::move(std::make_unique<m_Entity::Player>(m_context, pos));
}

void GameState::update(sf::Time deltaTime)
{
	if (m_Player != nullptr)
	{
		m_Player->update(deltaTime, keys);
	}
}

void GameState::processInput()
{
	while (m_context->m_window->pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
			m_context->m_window->close();
		else if (m_event.type == sf::Event::KeyPressed)
		{
			keys->push(m_event.key.code);
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			keys->push(100);
		}
	}
}

void GameState::render() 
{
	m_context->m_window->clear({ 200, 200, 200, 0 });

	//	render all entities
/*	for (auto it = m_entities.begin(); it != m_entities.end(); it++)
	{
		it->get()->render();
	}
	*/
	if (m_Player!=nullptr)
		m_Player->render();
	m_context->m_window->display();
}
