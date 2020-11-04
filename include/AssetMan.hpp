#pragma once
#include "State.hpp"

//  ID for fonts;
enum IDF 
{
    MAIN_FONT
};

//  ID for textures
enum IDT
{

};

namespace Engine
{
    //  basically ensures that each font and texture must only load once
    class AssetMan {
    private:
        std::vector<std::unique_ptr<sf::Texture>> m_textures;
        std::vector<std::unique_ptr<sf::Font>> m_fonts;

    public:
        AssetMan();
        ~AssetMan();

        void addFont(unsigned int id, const std::string &filePath);
        void addTexture(unsigned int id, const std::string &filePath);

   
        const sf::Texture &getTexture(unsigned int id) const;
        const sf::Font &getFont(unsigned int id) const;

        // etc
    };
};