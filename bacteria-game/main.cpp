#include <thread>

#include "render.h"
#include "keyboardhandler.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "SFML 3 Window");
    window.setActive(false);

    std::thread thread(&renderingThread, &window);

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
    }

    thread.join();
}

