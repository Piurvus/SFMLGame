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
    PWALK1,
    PWALK2,
    PWALK3,
    PWALK4,
    PWALK5,
    PWALK6,
    PWALK7,
    PWALK8,
    BOMB11,
    BOMB12,
    BOMB13,
    BOMB14,
    BOMB21,
    BOMB22,
    BOMB23,
    BOMB24,
    BOMB31,
    BOMB32,
    BOMB33,
    BOMB34,
    PDIE1,
    PDIE2,
    PDIE3,
    PDIE4,
    BLOCK1
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