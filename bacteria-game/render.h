#ifndef RENDER_H
#define RENDER_H

namespace sf
{
    class RenderWindow;
    class String;
}

sf::String getResourcePath(const sf::String& name);

void commonDraw(sf::RenderWindow& window);

void draw(sf::RenderWindow& window);

void renderingThread(sf::RenderWindow* window);

#endif // RENDER_H
