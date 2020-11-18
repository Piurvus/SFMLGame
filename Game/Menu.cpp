#include "Menu.hpp"

Menu::Menu(std::shared_ptr<Context>& m_context) :
    m_context(m_context), event(sf::Event()), playIsSelected(true), playIsClicked(false),
    exitIsSelected(false), exitIsClicked(false)
{
}

Menu::~Menu()
{

}

void Menu::init()
{
    //  add and set fonts
    m_context->m_assets->addFont(MAIN_FONT, "fonts/white_systemattic/White Systemattic.ttf");

    m_gameTitle.setFont(m_context->m_assets->getFont(MAIN_FONT));
    m_playButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
    m_exitButton.setFont(m_context->m_assets->getFont(MAIN_FONT));

    m_gameTitle.setString("Bomberman");
    m_gameTitle.setCharacterSize(static_cast<unsigned int>(0.35 * m_context->m_window->getSize().x));
    m_gameTitle.setFillColor(sf::Color(0, 100, 255));
    sf::FloatRect textRect = m_gameTitle.getLocalBounds();
    m_gameTitle.setOrigin(textRect.left + textRect.width / 2.0f,
                          textRect.top + textRect.height / 2.0f);
    m_gameTitle.setPosition(sf::Vector2f(m_context->m_window->getSize().x / 2.0f, m_context->m_window->getSize().y/ 6.0f));


    m_playButton.setString("Play");
    m_playButton.setCharacterSize(static_cast<unsigned int>(0.15 * m_context->m_window->getSize().x));
    m_playButton.setFillColor(sf::Color(0, 155, 175));
    sf::FloatRect textRect2 = m_playButton.getLocalBounds();
    m_playButton.setOrigin(textRect2.left + textRect2.width / 2.0f,
                          textRect2.top + textRect2.height / 2.0f);
    m_playButton.setPosition(sf::Vector2f(m_context->m_window->getSize().x / 2.0f, m_context->m_window->getSize().y / 2.0f));


    m_exitButton.setString("Exit");
    m_exitButton.setCharacterSize(static_cast<unsigned int>(0.15 * m_context->m_window->getSize().x));
    m_exitButton.setFillColor(sf::Color(0, 155, 175));
    sf::FloatRect textRect3 = m_exitButton.getLocalBounds();
    m_exitButton.setOrigin(textRect3.left + textRect3.width / 2.0f,
                          textRect3.top + textRect3.height / 2.0f);
    m_exitButton.setPosition(sf::Vector2f(m_context->m_window->getSize().x / 2.0f, m_context->m_window->getSize().y/ 2.0f + m_context->m_window->getSize().y / 5.0f));



} 
void Menu::update(sf::Time deltaTime)
{
    if (playIsSelected)
    {
        m_playButton.setFillColor(sf::Color(0, 255, 75));
        m_exitButton.setFillColor(sf::Color(0, 155, 175));
    }
    else if (exitIsSelected)
    {

        m_exitButton.setFillColor(sf::Color(0, 255, 75));
        m_playButton.setFillColor(sf::Color(0, 155, 175));
    }
    if (playIsClicked)
    {
        m_context->m_states->add(std::make_unique<GameState>(m_context));
        playIsClicked = false;
    }
    else if (exitIsClicked)
    {
        m_context->m_window->close();
    }
} 
void Menu::render()
{
    m_context->m_window->clear({200, 200, 200, 0});
    //  m_m_context->m_window->draw()
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->draw(m_playButton);
    m_context->m_window->draw(m_exitButton);

    m_context->m_window->display();
} 
void Menu::processInput()
{
    while(m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_context->m_window->close();
        else if (event.type == sf::Event::KeyPressed)
        {
            switch(event.key.code)
            {
                case sf::Keyboard::Up:
                {
                    playIsSelected = true;
                    playIsClicked = false;
                    exitIsClicked = false;
                    break;
                }
                case sf::Keyboard::Down:
                {
                    exitIsSelected = true;
                    exitIsClicked = false;
                    playIsSelected = false;
                    break;

                }
                case sf::Keyboard::Return:
                {
                    if (playIsSelected)
                        playIsClicked = true;
                    if (exitIsSelected)
                        exitIsClicked = true;
                    break;
                }
                default:
                {
                    
                }
            }
        }
    }
} 

