#pragma once
#include "State.hpp"
#include "Helper.hpp"
#include "GameState.h"

class Menu : public Engine::State {
private:

    std::shared_ptr<Context> m_context;
    
    sf::Event event;

    sf::Text m_gameTitle;
    sf::Text m_playButton;
    sf::Text m_exitButton;

    bool playIsSelected;
    bool playIsClicked;
    bool exitIsSelected;
    bool exitIsClicked;


public:
    Menu(std::shared_ptr<Context> &m_context);
    ~Menu();

    void init() override;
    void update(sf::Time deltaTime) override;
    void render() override;
    void processInput() override; 

};