#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <queue>
#include <cmath>

#include <vector>

namespace Engine
{
    class State {

    private:

    public:
        State(){};
        virtual ~State(){};

        void pause(){};
        void start(){};

        //  virtual = 0 means every inheritance has to implement those functions
        virtual void init() = 0;
        virtual void processInput() = 0;
        virtual void update(sf::Time deltaTime) = 0;
        virtual void render() = 0;
    };
};