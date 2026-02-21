#include "render.h"
#include <SFML/Graphics.hpp>
#include "rendercontext.h"

static int FPS = {};

sf::String getResourcePath(const sf::String& name)
{
    return "../resources/" + name;
}

void commonDraw(sf::RenderWindow& window, RenderContext* context)
{
    auto acccess = context->acquire();

    auto list = acccess->primitives();

    for (auto it = list.cbegin(); 
        it != list.cend(); 
        ++it)
    {
        window.draw(**it);
    }
}

void draw(sf::RenderWindow& window, RenderContext *context)
{
    commonDraw(window, context);

    sf::Font font(getResourcePath("arial.ttf").toAnsiString());

    sf::Text text(font);
    text.setString(std::to_string(FPS));
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    window.draw(text);
}

void renderingThread(sf::RenderWindow* window, RenderContext *context)
{
    sf::Clock clock;
    sf::Time elapsed;
    int current_fps = 0;

    // activate the window's context
    auto result = window->setActive(true);

    // the rendering loop
    while (window->isOpen())
    {
        elapsed += clock.restart();
        if (elapsed.asSeconds() >= 1)
        {
            FPS = current_fps;
            current_fps = 0;
            elapsed = {};
        }

        ++current_fps;

        window->clear(sf::Color::Black);
        draw(*window, context);
        window->display();
    }
}