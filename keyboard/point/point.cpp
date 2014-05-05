#include <iostream>

#include <SFML/Graphics.hpp>

#define HEIGHT 800
#define WIDTH 600

#define ABS(x) ((x < 0) ? -x : x)

bool isRunning = true;
int x = HEIGHT / 2;
int y = WIDTH / 2;

int handleKeyboardEvent(sf::Event::KeyEvent &e)
{
    x = x + HEIGHT;
    y = y + WIDTH;
    switch (e.code) {
    case sf::Keyboard::Escape: {
        isRunning = false;
    } break;
    case sf::Keyboard::Right: {
        x = x + 10;
    } break;
    case sf::Keyboard::Left: {
        x = x - 10;
    } break;
    case sf::Keyboard::Down: {
        y = y + 10;
    } break;
    case sf::Keyboard::Up: {
        y = y - 10;
    } break;
    }
    x = x % HEIGHT;
    y = y % WIDTH;
    std::cout << "(" << x << ", " << y << ")" << std::endl;;
    return 0;
}

int handleEvent(sf::Event &e)
{
    if (e.type == sf::Event::Closed) {
        isRunning = false;
        return 0;
    }
    if (e.type == sf::Event::KeyPressed)
        handleKeyboardEvent(e.key);
    return 0;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(HEIGHT, WIDTH), "point window");
    sf::Event event;
    sf::CircleShape circle(10.f);

    circle.setFillColor(sf::Color::Red);
    circle.setPosition(x, y);

    while (isRunning) {
        window.clear(sf::Color::Black);

        while (window.pollEvent(event)) {
            handleEvent(event);
        }

        circle.setPosition(x, y);

        window.draw(circle);
        window.display();
    }

    return 0;
}
