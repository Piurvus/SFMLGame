#include "GameState.h"
#include <iostream>

GameState::GameState(std::shared_ptr<Context>& m_context) :
	m_context(m_context), m_event(sf::Event()), keys(std::make_shared<std::queue<unsigned int>>()), m_Player(nullptr),
	m_gamefield(std::vector<std::vector<int>>()), squaresize(100), pause(false)
{
	init();
}

GameState::~GameState()
{
}

void GameState::init()
{
	m_context->m_assets->addTexture(PWALK1, "textures/Penguin-images-2/Animations/penguin_walk01.png");
	m_context->m_assets->addTexture(PWALK2, "textures/Penguin-images-2/Animations/penguin_walk02.png");
	m_context->m_assets->addTexture(PWALK3, "textures/Penguin-images-2/Animations/penguin_walk03.png");
	m_context->m_assets->addTexture(PWALK4, "textures/Penguin-images-2/Animations/penguin_walk04.png");
	m_context->m_assets->addTexture(PWALK5, "textures/Penguin-images-2/Animations/penguin_walk05.png");
	m_context->m_assets->addTexture(PWALK6, "textures/Penguin-images-2/Animations/penguin_walk06.png");
	m_context->m_assets->addTexture(PWALK7, "textures/Penguin-images-2/Animations/penguin_walk07.png");
	m_context->m_assets->addTexture(PWALK8, "textures/Penguin-images-2/Animations/penguin_walk08.png");
	m_context->m_assets->addTexture(BOMB1, "textures/bombs/bomb1.png");


	std::shared_ptr<sf::Vector2f> pos = std::move(std::make_shared<sf::Vector2f>(squaresize*1.f, squaresize*1.f));
	m_Player = std::move(std::make_unique<m_Entity::Player>(m_context, pos, squaresize));
	m_Player->setPosition({ 0, 0 });

	//	gamefield
	std::vector<int> row = std::vector<int>(m_context->m_window->getSize().x / squaresize);
	std::vector<std::vector<int>> field = std::vector<std::vector<int>>(m_context->m_window->getSize().y / squaresize, row);

	//	new field
	row = std::vector<int>(m_context->m_window->getSize().x);
	m_gamefield = std::vector<std::vector<int>>(m_context->m_window->getSize().y, row);

	for (unsigned int y = 0; y < m_context->m_window->getSize().y / squaresize; y++)
	{
		for (unsigned int x = 0; x < m_context->m_window->getSize().x / squaresize; x++)
		{
			if (y % 2 && x % 2)
			{
				for (int i = 0; i < squaresize; i++)
				{
					for (int j = 0; j < squaresize; j++)
					{
						m_gamefield[y * squaresize + i][x * squaresize + j] = 99;
					}
				}
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
			init();
		}
		m_Player->update(deltaTime, keys, m_gamefield, squaresize);
		if (m_Player->putBomb())
		{
			sf::Vector2f poss = m_Player->getPos();
			std::shared_ptr<sf::Vector2f> pos = std::move(std::make_shared<sf::Vector2f>
			(round(poss.y/squaresize)*squaresize, round(poss.x/squaresize)*squaresize));
			std::unique_ptr<Bomb> b = std::move(std::make_unique<Bomb>(m_context, pos, squaresize, *pos, 3));	//	power of the bomb
			m_Bombs.push_back(std::move(b));

			//	collision with the bombs
			for (int i = 0; i < squaresize; i++)
				for (int j = 0; j < squaresize; j++)
					m_gamefield[static_cast<unsigned int>(pos->y+i)][static_cast<unsigned int>(pos->x+j)] = 50;
		}
		
		/*	
			todo:
			- implement better logic for hitting bombs (you need to be able to move back to the square of the bomb without hitting it
			- you should be able to move with the bomb if you hit it (combos)
			- ...
		*/
		
		// r, l, d, u
		int dir = m_Player->hitBomb();
		if (dir)
		{
			sf::Vector2f pos = m_Player->getPos();
			for (unsigned int i = 0; i < m_Bombs.size(); i++)
			{
				switch (dir)
				{
				case 1:
					if (m_Bombs[i]->getPos().x == round(pos.x / squaresize) && m_Bombs[i]->getPos().y == round(pos.y / squaresize) + 1)
					{
						m_Bombs[i]->getHit(dir - 1);
						//m_Player->setPosition({ round(m_Player->getPos().y/squaresize)*squaresize , -1 });
					}
					break;
				case 2:
					if (m_Bombs[i]->getPos().x == round(pos.x / squaresize) && m_Bombs[i]->getPos().y == round(pos.y / squaresize) - 1)
					{
						m_Bombs[i]->getHit(dir - 1);
					}
					break;
				case 3:
					if (m_Bombs[i]->getPos().x == round(pos.x/squaresize)+1 && m_Bombs[i]->getPos().y == round(pos.y/squaresize))
						m_Bombs[i]->getHit(dir - 1);
					break;
				case 4:
					if (m_Bombs[i]->getPos().x == round(pos.x/squaresize)-1 && m_Bombs[i]->getPos().y == round(pos.y/squaresize))
						m_Bombs[i]->getHit(dir - 1);
					break;
				}
			}
		}
	}

	for (unsigned int i = 0; i < m_Shock.size(); i++)
	{
		if (m_Shock[i]->done())
			m_Shock.erase(m_Shock.begin() + i--);
		else	
			m_Shock[i]->update(deltaTime);
	}

	for (unsigned int i = 0; i < m_Bombs.size(); i++)
	{

		m_Bombs[i].get()->update(deltaTime, m_gamefield);

		//	the BOMB GOES puf
		if (m_Bombs[i]->goesBoom())
		{
			sf::Vector2i pos = m_Bombs[i]->getPos();
			int power = m_Bombs[i]->getStrength();
			
			//	first connect with other bombs and objects

			//	first search horizontal
			if (!(pos.x % 2))
			{
				for (int k = pos.y - power+1; k < pos.y + power; k++) {
					if (k < 0)
						continue;
					else if (k >= m_gamefield[0].size())
						break;
					//	maybe make shock class for the beam? so we can shock[i]->render(); and collision test and so forth,,,,

					std::shared_ptr<sf::Vector2f> position = std::move(std::make_shared<sf::Vector2f>
						( static_cast<float>(k*squaresize), static_cast<float>(pos.x*squaresize) ));

					//std::unique_ptr<Shock> shock = std::move(std::make_unique<Shock>(m_context, position, 100));

					m_Shock.push_back(std::move(std::make_unique<Shock>(m_context, position, 25, squaresize)));


					if (round(m_Player->getPos().x/squaresize) == pos.x && round(m_Player->getPos().y/squaresize) == k)
						m_Player->kill();

					//	look for other objects in the way
					for (unsigned int j = 0; j < m_Bombs.size(); j++) {
						if (j == i)
							continue;
						//std::cout <<"K: " << k << " " << m_Bombs[j]->getPos().y << std::endl;
						if (m_Bombs[j]->getPos().x == pos.x && m_Bombs[j]->getPos().y == k)
							m_Bombs[j]->goBoom();
					}
				}
			}
			if (!(pos.y % 2))
			{
				for (int k = pos.x - power + 1; k < pos.x + power; k++) {
					if (k < 0)
						continue;
					else if (k >= m_gamefield[0].size())
						break;


					std::shared_ptr<sf::Vector2f> position = std::move(std::make_shared<sf::Vector2f>
						( static_cast<float>(pos.y*squaresize), static_cast<float>(k*squaresize) ));

					m_Shock.push_back(std::move(std::make_unique<Shock>(m_context, position, 25, squaresize)));

					if (round(m_Player->getPos().x/squaresize) == k && round(m_Player->getPos().y/squaresize) == pos.y)
						m_Player->kill();

					for (unsigned int j = 0; j < m_Bombs.size(); j++) {
						if (j == i)
							continue;
						if (m_Bombs[j]->getPos().y == pos.y && m_Bombs[j]->getPos().x == k)
							m_Bombs[j]->goBoom();
					}
				}
			}

			//	if boom is complete we can erase the bomb
			//	first delete pos tho in field
			for (int k = 0; k < squaresize; k++)
				for (int j = 0; j < squaresize; j++)
					m_gamefield[pos.x*squaresize + k][pos.y*squaresize + j] = 0;
			m_Bombs.erase(m_Bombs.begin() + i);
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

	for (unsigned int i = 0; i < m_Shock.size(); i++)
	{
		m_Shock[i]->render();
	}

	sf::VertexArray line(sf::LinesStrip, 2);
	//	rows
	for (unsigned int i = 0; i < m_context->m_window->getSize().y; i+=squaresize)
	{
		line[0].position = sf::Vector2f(0.f, static_cast<float>(i));
		line[1].position = sf::Vector2f(static_cast<float>(m_context->m_window->getSize().x), static_cast<float>(i));

		m_context->m_window->draw(line);
	}

	//	columns
	for (unsigned int i = 0; i < m_context->m_window->getSize().x; i+=squaresize)
	{
		line[0].position = sf::Vector2f(static_cast<float>(i), 0.f);
		line[1].position = sf::Vector2f(static_cast<float>(i), static_cast<float>(m_context->m_window->getSize().y));

		m_context->m_window->draw(line);
	}


	m_context->m_window->draw(line);


	sf::RectangleShape obst;
	obst.setSize({ static_cast<float>(squaresize), static_cast<float>(squaresize) });
	obst.setFillColor({ 150, 255, 255 });

	//	new field drawing
	for (unsigned int y = 0; y < m_gamefield.size(); y+= squaresize)
	{
		for (unsigned int x = 0; x < (m_gamefield.begin()+y)->size(); x+=squaresize)
		{
			if(m_gamefield.size() > 0)
			{
				if (m_gamefield[y][x] == 99)
				{
					obst.setPosition({ static_cast<float>(x), static_cast<float>(y) });
					obst.setFillColor({ 150, 255, 255 });
					m_context->m_window->draw(obst);
				}
			}
		}
	}
	if (m_Player!=nullptr)
		m_Player->render();
	m_context->m_window->display();
}
