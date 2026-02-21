#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include <set>
#include <optional>
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

template<typename T>
class Set : public std::set<T>
{
public:
    bool contains(const T& value) const
    {
        return find(value) != cend();
    }
};

class KeyboardHandler
{
public:
    typedef Set<sf::Keyboard::Scancode> PressedKeyArray;
    void addHandler(std::function<void(PressedKeyArray)>);

    void keyPressed(const std::optional<sf::Event>& e);
    void keyReleased(const std::optional<sf::Event>& e);
    
private:
    void processHandlers();
    PressedKeyArray m_pressed_key_array;
    std::vector<std::function<void(PressedKeyArray)>> m_handler_array;
};


#endif // !KEYBOARDHANDLER_H
