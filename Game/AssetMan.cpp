#include "AssetMan.hpp"
#include <iostream>

Engine::AssetMan::AssetMan() 
{

}

Engine::AssetMan::~AssetMan() 
{

}

void Engine::AssetMan::addFont(unsigned int id, const std::string &filePath)
{
    std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();

    //  check if already loaded
    if ( id < m_fonts.size() && m_fonts.at(id) != nullptr )
        return;

    //  if not loaded yet load it
    font->loadFromFile(filePath);

    //  make sure there is enough space
    while (id >= m_fonts.size())
        m_fonts.push_back(nullptr);

    m_fonts[id] = std::move(font);
}
void Engine::AssetMan::addTexture(unsigned int id, const std::string &filePath)
{
    std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();

    //  check if already loaded
    if ( id < m_textures.size() && m_textures.at(id) != nullptr )
        return;
    
    //  load it
    if (!texture->loadFromFile(filePath))
        return;

    //  make sure there is enough space
	while (id >= m_textures.size())
        m_textures.push_back(nullptr);
    m_textures[id] = std::move(texture);

}


const sf::Texture &Engine::AssetMan::getTexture(unsigned int id) const
{
    if (m_textures.size() > id)
        return *m_textures.at(id).get();

    //  dunno if this rlly works -> could be cause of error
    return sf::Texture();
} 
const sf::Font &Engine::AssetMan::getFont(unsigned int id) const 
{
    if (m_fonts.size() > id)
        return *m_fonts.at(id).get();

    //  same as above
    return *m_fonts.at(id).get();
}

