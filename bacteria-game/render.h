#ifndef RENDER_H
#define RENDER_H

namespace sf
{
    class RenderWindow;
    class String;
}

namespace std
{
    class mutex;
}

class RenderContext;


sf::String getResourcePath(const sf::String& name);

void commonDraw(sf::RenderWindow& window, RenderContext* context);

void draw(sf::RenderWindow& window, RenderContext* context);

void renderingThread(sf::RenderWindow* window, RenderContext* context);

#endif // RENDER_H
