#include <thread>

#include "render.h"
#include "keyboardhandler.h"
#include "rendercontext.h"

static const sf::Texture wood_texture = sf::Texture(getResourcePath("wood.jpg").toAnsiString());

static const sf::Texture glass_ball_texture = sf::Texture(getResourcePath("glass_ball.png").toAnsiString());


int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "SFML 3 Window");
    window.setActive(false);



    RenderContext context;
    {
        auto access = context.acquire();

        auto circle = new sf::CircleShape(100);
        circle->setPosition({ 100,100 });
        circle->setFillColor(sf::Color::Red);
        access->addPrimitive(circle);

        auto rect = new sf::RectangleShape({ 200,200 });
        rect->setPosition({ 200,200 });
        rect->setFillColor(sf::Color::Green);
        access->addPrimitive(rect);

        auto triangle = new sf::CircleShape(100, 3);
        triangle->rotate(sf::degrees(10));
        access->addPrimitive(triangle);

        auto convex = new sf::ConvexShape(5);
        int offset = 400;
        convex->setPoint(0, { 0.f + offset, 0.f });
        convex->setPoint(1, { 150.f + offset, 10.f });
        convex->setPoint(2, { 120.f + offset, 90.f });
        convex->setPoint(3, { 30.f + offset, 100.f });
        convex->setPoint(4, { 0.f + offset, 50.f });
        convex->setFillColor(sf::Color(60, 190, 130));
        access->addPrimitive(convex);

        auto trect = new sf::RectangleShape({ 300, 300 });
        trect->setPosition({ 450,200 });
        trect->setTexture(&wood_texture);
        trect->setFillColor(sf::Color::Magenta);
        access->addPrimitive(trect);

        auto ball = new sf::Sprite(glass_ball_texture);
        ball->setPosition({ 0, 400 });
        ball->setColor(sf::Color(122, 191, 255));
        access->addPrimitive(ball);
    }
    

    std::thread thread(&renderingThread, &window, &context);

    KeyboardHandler keyboard_handler;

    auto tmp_item = new sf::RectangleShape({ 300, 300 });
    tmp_item->setPosition({ 200,200 });
    auto addRemoveFunc = [tmp_item, &context](KeyboardHandler::PressedKeyArray array)
    {
            if (array.contains(sf::Keyboard::Scancode::Space))
                context.acquire()->addPrimitive(tmp_item);
            else
                context.acquire()->removePrimitive(tmp_item);
                
    };
    keyboard_handler.addHandler(addRemoveFunc);


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
            {
                keyboard_handler.keyReleased(event);
            }
        }
    }

    delete tmp_item;

    thread.join();
}

