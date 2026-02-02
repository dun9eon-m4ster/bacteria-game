#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <vector>
#include <iostream>
#include <set>
#include <string>


template<typename T>
std::ostream& operator <<(std::ostream& stream, const std::set<T>& v)
{
    stream << '[';
    for (auto it = v.cbegin(); it != v.cend(); ++it)
    {
        stream << *it;
        //if (it + 1 != v.cend())
            stream << ',';
    }
    stream << ']' << std::endl;
    return stream;
}

std::ostream& operator <<(std::ostream& stream, const sf::Keyboard::Scancode& v)
{
    auto str = sf::Keyboard::getDescription(v).toAnsiString();
    return stream << str;
}

class KeyboardHandler
{
    std::set<sf::Keyboard::Scancode> m_pressed_key_array;
public:
    void keyPressed(const std::optional<sf::Event> &e)
    {
        auto key_press = e->getIf<sf::Event::KeyPressed>();
        if (m_pressed_key_array.find(key_press->scancode) == m_pressed_key_array.end())
        {
            m_pressed_key_array.insert(key_press->scancode);
            std::cout << m_pressed_key_array << std::endl;
        }
        
    }

    void keyReleased(const std::optional<sf::Event>& e)
    {
        auto key_release = e->getIf<sf::Event::KeyReleased>();
        m_pressed_key_array.erase(m_pressed_key_array.find(key_release->scancode));
        std::cout << m_pressed_key_array << std::endl;
    }
};

int main()
{
    std::vector<int> v{1, 2, 3, 4, 5};

    //std::cout << v << std::endl;

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML 3 Window");
    KeyboardHandler keyboard_handler;


    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (event->is<sf::Event::KeyPressed>())
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                    window.close();
                else
                    keyboard_handler.keyPressed(event);
            }
            else if (event->is<sf::Event::KeyReleased>())
                keyboard_handler.keyReleased(event);
        }

        window.clear({0,0,255});
        window.display();
    }
}

