#include "GameState.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

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
	m_context->m_assets->addTexture(BOMB11, "textures/bombs/bomb11.png");
	m_context->m_assets->addTexture(BOMB12, "textures/bombs/bomb12.png");
	m_context->m_assets->addTexture(BOMB13, "textures/bombs/bomb13.png");
	m_context->m_assets->addTexture(BOMB14, "textures/bombs/bomb14.png");
	m_context->m_assets->addTexture(BOMB21, "textures/bombs/bomb21.png");
	m_context->m_assets->addTexture(BOMB22, "textures/bombs/bomb22.png");
	m_context->m_assets->addTexture(BOMB23, "textures/bombs/bomb23.png");
	m_context->m_assets->addTexture(BOMB24, "textures/bombs/bomb24.png");
	m_context->m_assets->addTexture(BOMB31, "textures/bombs/bomb31.png");
	m_context->m_assets->addTexture(BOMB32, "textures/bombs/bomb32.png");
	m_context->m_assets->addTexture(BOMB33, "textures/bombs/bomb33.png");
	m_context->m_assets->addTexture(BOMB34, "textures/bombs/bomb34.png");
	m_context->m_assets->addTexture(PDIE1, "textures/Penguin-images-2/Animations/penguin_die01.png");
	m_context->m_assets->addTexture(PDIE2, "textures/Penguin-images-2/Animations/penguin_die02.png");
	m_context->m_assets->addTexture(PDIE3, "textures/Penguin-images-2/Animations/penguin_die03.png");
	m_context->m_assets->addTexture(PDIE4, "textures/Penguin-images-2/Animations/penguin_die04.png");
	m_context->m_assets->addTexture(BLOCK1, "textures/blocks/block1.png");
	m_context->m_assets->addTexture(BLOCK2, "textures/blocks/block2.png");

	block1.setTexture(m_context->m_assets->getTexture(BLOCK1));
	block1.setScale({ 0.4f, 0.4f });

	background.setTexture(m_context->m_assets->getTexture(BACKGROUND1));
	background.setScale({ 0.4f, 0.4f });

	std::shared_ptr<sf::Vector2f> pos = std::move(std::make_shared<sf::Vector2f>(squaresize * 1.f, squaresize * 1.f));
	m_Player = std::move(std::make_unique<m_Entity::Player>(m_context, pos, squaresize));
	m_Player->setPosition({ 0.f, 0.f });

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

	//	PUT DOWN BLOCKS
	srand((unsigned)time(0));
	unsigned int sizex = m_context->m_window->getSize().x;
	unsigned sizey = m_context->m_window->getSize().y;

	for (int i = 0; i < 40; i++) {

		unsigned int x = (rand() % sizex);
		unsigned int y = (rand() % sizey);
		
		if (x / squaresize < 3 && y / squaresize < 3 || ((x / squaresize) % 2 && (y / squaresize) % 2)) {
			i--;
			continue;
		}

		pos = std::move(std::make_shared<sf::Vector2f>(static_cast<float>(round(y/squaresize)*squaresize), 
			static_cast<float>(round(x/squaresize)*squaresize)));

		std::unique_ptr<Block> b = std::move(std::make_unique<Block>(m_context, pos, squaresize));
		m_Blocks.push_back(std::move(b));

		for (int i = 0; i < squaresize; i++)
			for (int j = 0; j < squaresize; j++)
				m_gamefield[static_cast<unsigned int>(pos->x+i)][static_cast<unsigned int>(pos->y+j)] = 20;


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
			background.setTexture(m_context->m_assets->getTexture(BACKGROUND2));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
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
				bool stopl = false;
				bool stopu = false;
				//for (unsigned int k = pos.y - power+1; k < static_cast<unsigned int>(pos.y + power); k++) {
				for (unsigned int k = 0; k < power; k++) {
					unsigned int u = pos.y + k;
					unsigned int l = pos.y - k;

					if (l < 0)
						continue;
					else if (u >= m_gamefield[0].size())
						break;
					//	maybe make shock class for the beam? so we can shock[i]->render(); and collision test and so forth,,,,

					std::shared_ptr<sf::Vector2f> position1 = std::move(std::make_shared<sf::Vector2f>
						( static_cast<float>(u*squaresize), static_cast<float>(pos.x*squaresize) ));
					std::shared_ptr<sf::Vector2f> position2 = std::move(std::make_shared<sf::Vector2f>
						( static_cast<float>(l*squaresize), static_cast<float>(pos.x*squaresize) ));


					//std::unique_ptr<Shock> shock = std::move(std::make_unique<Shock>(m_context, position, 100));

					if (!stopu)
						m_Shock.push_back(std::move(std::make_unique<Shock>(m_context, position1, 25, squaresize)));
					if (u != l && !stopl)
						m_Shock.push_back(std::move(std::make_unique<Shock>(m_context, position2, 25, squaresize)));


					if (round(m_Player->getPos().x/squaresize) == pos.x && round(m_Player->getPos().y/squaresize) == l && !stopl)
						m_Player->kill();
					if (round(m_Player->getPos().x/squaresize) == pos.x && round(m_Player->getPos().y/squaresize) == u && !stopu)
						m_Player->kill();

					//	look for other objects in the way
					for (unsigned int j = 0; j < m_Bombs.size(); j++) {
						if (j == i)
							continue;
						//std::cout <<"K: " << k << " " << m_Bombs[j]->getPos().y << std::endl;
						if (m_Bombs[j]->getPos().x == pos.x && m_Bombs[j]->getPos().y == u && !stopu)
							m_Bombs[j]->goBoom();
						if (m_Bombs[j]->getPos().x == pos.x && m_Bombs[j]->getPos().y == l && !stopl)
							m_Bombs[j]->goBoom();
					}
					for (unsigned int j = 0; j < m_Blocks.size(); j++) {
						if (j == i)
							continue;
						if (m_Blocks[j]->getPos(squaresize).y == pos.x && m_Blocks[j]->getPos(squaresize).x == u && !stopu) {
							//	BLOCK PUF
							stopu = true;
							sf::Vector2i posss = m_Blocks[j]->getPos(squaresize);
							m_Blocks.erase(m_Blocks.begin() + j);
							//	delete object in field

							for (int i = 0; i < squaresize; i++)
								for (int j = 0; j < squaresize; j++)
									m_gamefield[posss.y*squaresize+i][posss.x*squaresize+j] = 0;

						}
						if (m_Blocks[j]->getPos(squaresize).y == pos.x && m_Blocks[j]->getPos(squaresize).x == l && !stopl) {
							//	BLOCK PUF
							stopl = true;
							sf::Vector2i posss = m_Blocks[j]->getPos(squaresize);
							m_Blocks.erase(m_Blocks.begin() + j);
							std::cout << j;
							//	delete object in field

							for (int i = 0; i < squaresize; i++)
								for (int j = 0; j < squaresize; j++)
									m_gamefield[posss.y*squaresize+i][posss.x*squaresize+j] = 0;

						}
					}
				}
			}
			if (!(pos.y % 2))
			{
				for (unsigned int k = pos.x - power + 1; k < static_cast<unsigned int>(pos.x + power); k++) {
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
					for (unsigned int j = 0; j < m_Blocks.size(); j++) {
						if (j == i)
							continue;
						if (m_Blocks[j]->getPos(squaresize).x == pos.y && m_Blocks[j]->getPos(squaresize).y == k) {
							sf::Vector2i posss = m_Blocks[j]->getPos(squaresize);
							m_Blocks.erase(m_Blocks.begin() + j);
							//	delete object in field

							for (int i = 0; i < squaresize; i++)
								for (int j = 0; j < squaresize; j++)
									m_gamefield[posss.y*squaresize+i][posss.x*squaresize+j] = 0;


						}
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
	m_context->m_window->clear();

	m_context->m_window->draw(background);

	for (unsigned int i = 0; i < m_Bombs.size(); i++)
	{
		m_Bombs[i]->render();
	}

	for (unsigned int i = 0; i < m_Shock.size(); i++)
	{
		m_Shock[i]->render();
	}
	
	for (unsigned int i = 0; i < m_Blocks.size(); i++)
	{
		m_Blocks[i]->render();
	}

	//	new field drawing
	for (unsigned int y = 0; y < m_gamefield.size(); y+= squaresize)
	{
		for (unsigned int x = 0; x < (m_gamefield.begin()+y)->size(); x+=squaresize)
		{
			if(m_gamefield.size() > 0)
			{
				if (m_gamefield[y][x] == 99) {
					block1.setPosition({ static_cast<float>(x), static_cast<float>(y) });
					m_context->m_window->draw(block1);
				}
			}
		}
	}
	if (m_Player!=nullptr)
		m_Player->render();
	m_context->m_window->display();
}
