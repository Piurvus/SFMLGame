#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <memory>

#include <vector>

namespace Engine
{
    class State {

    private:
        std::vector<sf::Texture> textures;

    public:
        State();
        virtual ~State();

        void pause(){};
        void start(){};

        //  virtual = 0 means every inheritance has to implement those functions
        virtual void init() = 0;
        virtual void processInput() = 0;
        virtual void update() = 0;
        virtual void render() = 0;
    };
};