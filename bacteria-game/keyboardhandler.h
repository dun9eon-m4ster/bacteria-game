#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include <set>
#include <vector>
#include <iostream>
#include <string>
#include <thread>
#include <optional>

#include <SFML/Graphics.hpp>

#include <SFML/Window/Keyboard.hpp>



class KeyboardHandler
{
    std::set<sf::Keyboard::Scancode> m_pressed_key_array;
public:
    void keyPressed(const std::optional<sf::Event>& e);
    void keyReleased(const std::optional<sf::Event>& e);
};

template<typename T>
std::ostream& operator <<(std::ostream& stream, const std::set<T>& v)
{
    stream << '[';
    for (auto it = v.cbegin(); it != v.cend(); ++it)
    {
        stream << *it << ',';
    }
    stream << ']' << std::endl;
    return stream;
}

std::ostream& operator <<(std::ostream& stream, const sf::Keyboard::Scancode& v);

#endif // !KEYBOARDHANDLER_H
