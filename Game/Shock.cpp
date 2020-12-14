#include "Shock.h"

void Shock::update(sf::Time deltaTime)
{
	this->health--;
	blue += 2;
}

void Shock::render()
{
	this->pos->setFillColor({ 150, 150, sf::Uint8(blue) });
	this->m_context->m_window->draw(*this->pos);
}

const bool Shock::done() const
{
	return this->health <= 0;
}
