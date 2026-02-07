#include "render.h"
#include <SFML/Graphics.hpp>

static int FPS = {};

static const sf::Texture wood_texture = sf::Texture(getResourcePath("wood.jpg").toAnsiString());

static const sf::Texture glass_ball_texture = sf::Texture(getResourcePath("glass_ball.png").toAnsiString());

sf::String getResourcePath(const sf::String& name)
{
    return "../resources/" + name;
}

void commonDraw(sf::RenderWindow& window)
{
    sf::CircleShape circle(100);
    circle.setPosition({ 100,100 });
    circle.setFillColor(sf::Color::Red);
    window.draw(circle);

    sf::RectangleShape rect({ 200,200 });
    rect.setPosition({ 200,200 });
    rect.setFillColor(sf::Color::Green);
    window.draw(rect);

    sf::CircleShape triangle(100, 3);
    triangle.rotate(sf::degrees(10));
    window.draw(triangle);

    int offset = 400;
    sf::ConvexShape convex(5);
    convex.setPoint(0, { 0.f + offset, 0.f });
    convex.setPoint(1, { 150.f + offset, 10.f });
    convex.setPoint(2, { 120.f + offset, 90.f });
    convex.setPoint(3, { 30.f + offset, 100.f });
    convex.setPoint(4, { 0.f + offset, 50.f });
    convex.setFillColor(sf::Color(60, 190, 130));
    window.draw(convex);

    sf::RectangleShape trect({ 300, 300 });
    trect.setPosition({ 450,200 });
    trect.setTexture(&wood_texture);
    trect.setFillColor(sf::Color::Magenta);
    window.draw(trect);


    sf::Sprite ball(glass_ball_texture);
    ball.setPosition({0, 400});
    ball.setColor(sf::Color(122,191,255));
    window.draw(ball);
}

void draw(sf::RenderWindow& window)
{
    commonDraw(window);

    sf::Font font(getResourcePath("arial.ttf").toAnsiString());

    sf::Text text(font);
    text.setString(std::to_string(FPS));
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    window.draw(text);
}

void renderingThread(sf::RenderWindow* window)
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
        draw(*window);
        window->display();
    }
}