#include "Block.h"

void Block::init()
{
	sprite.setTexture(m_context->m_assets->getTexture(BLOCK2));
	sprite.setPosition({ this->pos->getGlobalBounds().top, this->pos->getGlobalBounds().left });
	sprite.setScale({ 0.4f, 0.4f });
}

void Block::update(sf::Time deltatime)
{
}

const int Block::getHit() const
{
	//	returns a int according to powerup.

	return 0;
}

void Block::render()
{
	m_context->m_window->draw(sprite);
}
