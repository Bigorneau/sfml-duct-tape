#include <unistd.h>

#include <iostream>

#include <SFML/Graphics.hpp>

#include <X11/Xlib.h>

#define HEIGHT 800
#define WIDTH 600

bool isRunning = true;
struct s_point {
    int x;
    int y;
};
struct s_point point = { HEIGHT / 2, WIDTH / 2 };

int move(int x, int y)
{
    int xx, yy;
    xx = HEIGHT;
    yy = WIDTH;
    xx = xx + point.x + x;
    yy = yy + point.y + y;
    // bounds
    point.x = xx % HEIGHT;
    point.y = yy % WIDTH;
    std::cout << "(" << point.x << ", " << point.y << ")" << std::endl;
    return 0;
}

int readKeyboard(int delta)
{
    int x, y;
    while (isRunning) {
        x = 0;
        y = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            isRunning = false;
            break;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            x = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            x = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            y = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            y = -1;
        }
        if (x != 0 || y != 0)
            move(x, y);
        usleep(200);
    }
    return 0;
}

int main()
{
    XInitThreads();

    sf::RenderWindow window(sf::VideoMode(HEIGHT, WIDTH), "point window");
    sf::Event event;
    sf::CircleShape circle(10.f);
    sf::Thread keyboardThread(&readKeyboard, 0);

    window.setActive(false);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(point.x, point.y);
    keyboardThread.launch();

    while (isRunning) {
        window.clear(sf::Color::Black);

        circle.setPosition(point.x, point.y);

        window.draw(circle);
        window.display();
    }

    keyboardThread.terminate();
    keyboardThread.wait();

    return 0;
}
