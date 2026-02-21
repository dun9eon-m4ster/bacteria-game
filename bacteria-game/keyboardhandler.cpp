#include "keyboardhandler.h"

void KeyboardHandler::addHandler(std::function<void(PressedKeyArray)> handler)
{
    m_handler_array.push_back(handler);
}

void KeyboardHandler::keyPressed(const std::optional<sf::Event>& e)
{
    auto key_press = e->getIf<sf::Event::KeyPressed>();
    if (!m_pressed_key_array.contains(key_press->scancode))
    {
        m_pressed_key_array.insert(key_press->scancode);
        processHandlers();
    }
}

void KeyboardHandler::keyReleased(const std::optional<sf::Event>& e)
{
    auto key_release = e->getIf<sf::Event::KeyReleased>();
    m_pressed_key_array.erase(m_pressed_key_array.find(key_release->scancode));
    processHandlers();
}

void KeyboardHandler::processHandlers()
{
    for (auto it = m_handler_array.begin(); it != m_handler_array.end(); ++it)
    {
        auto func = *it; 
        func(m_pressed_key_array);
    }
}
