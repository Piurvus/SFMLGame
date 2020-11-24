#include "GameState.h"

GameState::GameState(std::shared_ptr<Context>& m_context) :
	m_context(m_context), m_event(sf::Event()), keys(std::make_shared<std::queue<unsigned int>>()), m_Player(nullptr),
	m_Field(nullptr), squaresize(100), pause(false)
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
	if (pause)
	{
		pause = false;
		m_context->m_states->add(std::make_unique<Pause>(m_context));
	}
	if (m_Player != nullptr)
	{
		if (m_Player->isDead())
		{
			std::shared_ptr<sf::Vector2f> pos = std::move(std::make_shared<sf::Vector2f>(squaresize*1.f, squaresize*1.f));
			m_Player = std::move(std::make_unique<m_Entity::Player>(m_context, pos));
		}
		m_Player->update(deltaTime, keys, m_Field);
	}
	for (unsigned int i = 0; i < m_Bombs.size(); i++)
	{
		m_Bombs[i].get()->update(deltaTime, m_Field);

		//	the BOMB GOES puf
		if (m_Bombs[i]->goesBoom())
		{
			//	action happening here

			//	first we get the dates
			sf::Vector2i pos = m_Bombs[i]->getPos();	//	position already /sqaURE

			//	bomb spot to explosion color ==18
			*((m_Field->begin() + pos.y)->begin() + pos.x) = 18;

			int strength = m_Bombs[i]->getStrength();	

			m_Bombs.erase(m_Bombs.begin() + i);
			//	loop through each position and see if there is something

			sf::Vector2i plpos = m_Player->getPos(squaresize);

			//	vertical boom
			for (int k = (pos.x - strength>=0)? pos.x-strength:0; k <= pos.x+strength; k++)
			{
				if (!(pos.y % 2) && k < static_cast<int>(m_Field->size()))
				{
					if (*((m_Field->begin() + pos.y)->begin() + k) == 19)
					{
						for (unsigned int j = 0; j < m_Bombs.size(); j++)
						{
							if (m_Bombs[j]->getPos().x == k)
								m_Bombs[j]->goBoom();
						}
					}
					*((m_Field->begin() + pos.y)->begin() + k) = 18;
					if (*((m_Field->begin() + plpos.y)->begin() + plpos.x) >= 5 && *((m_Field->begin() + plpos.y)->begin() + plpos.x) <= 18)
						m_Player->kill();
				}
			}

			//	horizontal boom
			for (int k = (pos.y - strength >= 0) ? pos.y - strength : 0; k <= pos.y + strength; k++)
			{
				if (!(pos.x % 2) && k < static_cast<int>(m_Field->begin()->size()))
				{
					if (*((m_Field->begin() + k)->begin() + pos.x) == 19)
					{
						for (unsigned int j = 0; j < m_Bombs.size(); j++)
						{
							if (m_Bombs[j]->getPos().y == k)
								m_Bombs[j]->goBoom();
						}
					}

					//	
					if (*((m_Field->begin() + k)->begin() + pos.x) >= 21 && *((m_Field->begin() + k)->begin() + pos.x) <= 24)
					{/*
						Bomb* hit;
						
						hit->getHit(*((m_Field->begin() + k)->begin() + pos.x) - 21);
					*/}




					*((m_Field->begin() + k)->begin() + pos.x) = 18;
					if (*((m_Field->begin() + plpos.y)->begin() + plpos.x) >= 5 && *((m_Field->begin() + plpos.y)->begin() + plpos.x) <= 18)
						m_Player->kill();

				}
			}


			//	reaction with other bombs






		}
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
			if (m_event.key.code == sf::Keyboard::Tab)
				pause = true;
			else
			{
				keys->push(m_event.key.code);
			}
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

	for (unsigned int i = 0; i < m_Bombs.size(); i++)
	{
		m_Bombs[i]->render();
	}

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
			//	creating the REAL bombs
			if (*((m_Field->begin() + i)->begin() + j) == 20)
			{
				std::shared_ptr<sf::Vector2f> pos = std::move(std::make_shared<sf::Vector2f>(static_cast<float>(squaresize*i), static_cast<float>(squaresize*j)));
				sf::Vector2f poss = { static_cast<float>(squaresize * i), static_cast<float>(squaresize * j) };
				std::unique_ptr<Bomb> b = std::move(std::make_unique<Bomb>(m_context, pos, squaresize, poss, 3));	//	power of the bomb
				m_Bombs.push_back(std::move(b));
				*((m_Field->begin() + i)->begin() + j) = 19;
			}
			
			if (*((m_Field->begin() + i)->begin() + j) >= 5 &&*((m_Field->begin() + i)->begin() + j) <= 18)
			{
				obst.setPosition({ static_cast<float>(i * squaresize), static_cast<float>(j * squaresize) });
				obst.setFillColor({ 150, 150, 255 });
				m_context->m_window->draw(obst);
				*((m_Field->begin() + i)->begin() + j) -= 1;
				if (*((m_Field->begin() + i)->begin() + j) == 4)
					*((m_Field->begin() + i)->begin() + j) = 0;
			}
			
		}
	}

	if (m_Player!=nullptr)
		m_Player->render();
	m_context->m_window->display();
}
