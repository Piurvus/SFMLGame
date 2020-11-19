#pragma once
#include "State.hpp"
#include "StateMan.hpp"
#include "Helper.hpp"

class Pause : public Engine::State
{
private:
	std::shared_ptr<Context> m_context;

    bool backtomenu, goback;

    sf::Event m_event;

public:
    Pause(std::shared_ptr<Context> context);
    ~Pause();

    void init() override;
    void update(sf::Time deltaTime) override;
    void render() override;
    void processInput() override; 



};
