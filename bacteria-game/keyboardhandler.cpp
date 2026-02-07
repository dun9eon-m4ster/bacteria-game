#include "keyboardhandler.h"

void KeyboardHandler::keyPressed(const std::optional<sf::Event>& e)
{
    auto key_press = e->getIf<sf::Event::KeyPressed>();
    if (m_pressed_key_array.find(key_press->scancode) == m_pressed_key_array.end())
    {
        m_pressed_key_array.insert(key_press->scancode);
        std::cout << m_pressed_key_array << std::endl;
    }
}

void KeyboardHandler::keyReleased(const std::optional<sf::Event>& e)
{
    auto key_release = e->getIf<sf::Event::KeyReleased>();
    m_pressed_key_array.erase(m_pressed_key_array.find(key_release->scancode));
    std::cout << m_pressed_key_array << std::endl;
}

std::ostream& operator <<(std::ostream& stream, const sf::Keyboard::Scancode& v)
{
    auto str = sf::Keyboard::getDescription(v).toAnsiString();
    return stream << str;
}