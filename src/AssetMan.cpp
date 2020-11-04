#include "AssetMan.hpp"

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
    m_fonts[id] = std::move(font);
}
void Engine::AssetMan::addTexture(unsigned int id, const std::string &filePath)
{
    std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();

    //  check if already loaded
    if ( id < m_textures.size() && m_textures.at(id) != nullptr )
        return;
    
    //  load it
    texture->loadFromFile(filePath);
    m_textures[id] = std::move(texture);

}


const sf::Texture &Engine::AssetMan::getTexture(unsigned int id) const
{
    return *m_textures.at(id).get();
} 
const sf::Font &Engine::AssetMan::getFont(unsigned int id) const 
{
    return *m_fonts.at(id).get();
}

