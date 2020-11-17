#include "GameState.h"

GameState::GameState(std::shared_ptr<Context>& m_context) :
	m_context(m_context), m_event(sf::Event()), keys(std::make_shared<std::queue<unsigned int>>()), m_Player(nullptr),
	m_Field(nullptr), squaresize(100)
{
	init();
}

GameState::~GameState()
{
}

void GameState::init()
{
	std::shared_ptr<sf::Vector2f> pos = std::move(std::make_shared<sf::Vector2f>(squaresize*1.f, squaresize*1.f));
	m_Player = std::move(std::make_unique<m_Entity::Player>(m_context, pos));

	//	gamefield
	std::vector<int> row = std::vector<int>(m_context->m_window->getSize().x / squaresize);
	std::vector<std::vector<int>> field = std::vector<std::vector<int>>(m_context->m_window->getSize().y / squaresize, row);
	m_Field = std::make_shared<std::vector<std::vector<int>>> (std::move(field));

	for (unsigned int i = 0; i < m_Field->size(); i++)
	{
		for (unsigned int j = 0; j < (m_Field->begin() + i)->size(); j++)
		{
			if (j % 2 && i % 2)
			{
				*((m_Field->begin() + i)->begin()+j) = 1;
			}
		}
	}
}

void GameState::update(sf::Time deltaTime)
{
	if (m_Player != nullptr)
	{
		m_Player->update(deltaTime, keys, m_Field);
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


	
	sf::VertexArray line(sf::LinesStrip, 2);
	//	rows
	for (unsigned int i = 0; i < m_Field->size(); i++)
	{
		line[0].position = sf::Vector2f(0.f, static_cast<float>(i*squaresize));
		line[1].position = sf::Vector2f(static_cast<float>(m_context->m_window->getSize().x), static_cast<float>(i*squaresize));

		m_context->m_window->draw(line);
	}

	//	columns
	for (unsigned int i = 0; i < m_Field->begin()->size(); i++)
	{
		line[0].position = sf::Vector2f(static_cast<float>(i*squaresize), 0.f);
		line[1].position = sf::Vector2f(static_cast<float>(i*squaresize), static_cast<float>(m_context->m_window->getSize().y));

		m_context->m_window->draw(line);
	}



	m_context->m_window->draw(line);


	sf::RectangleShape obst;
	obst.setSize({ static_cast<float>(squaresize), static_cast<float>(squaresize) });
	obst.setFillColor({ 150, 255, 255 });

	for (unsigned int i = 0; i < m_Field->size(); i++)
	{
		for (unsigned int j = 0; j < (m_Field->begin()+i)->size(); j++)
		{
			if (*((m_Field->begin() + i)->begin() + j) == 1)
			{
				obst.setPosition({ static_cast<float>(i * squaresize), static_cast<float>(j * squaresize) });
				obst.setFillColor({ 150, 255, 255 });
				m_context->m_window->draw(obst);
			}
			if (*((m_Field->begin() + i)->begin() + j) >= 10)
			{
				obst.setPosition({ static_cast<float>(i * squaresize), static_cast<float>(j * squaresize) });
				obst.setFillColor({ 255, 150, 150 });
				m_context->m_window->draw(obst);
			}

		}
	}

	if (m_Player!=nullptr)
		m_Player->render();
	m_context->m_window->display();
}
