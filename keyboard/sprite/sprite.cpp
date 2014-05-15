#include <iostream>

#include <SFML/Graphics.hpp>

#define HEIGHT 800
#define WIDTH 600
#define TEXTURE_PATH "sprites/soldat.png"

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

int readKeyboard()
{
    int x, y;
    x = 0;
    y = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        return -1;
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
    return 0;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(HEIGHT, WIDTH), "point window");
    sf::Event event;
    sf::Texture texture;
    sf::Sprite sprite;

    if (!texture.loadFromFile(TEXTURE_PATH))
        return -1;
    texture.setSmooth(true);
    texture.setRepeated(false);

    sprite.setTexture(texture);
    sprite.setPosition(point.x, point.y);

    window.setActive(false);

    while (isRunning) {
        window.clear(sf::Color::Black);

        if (readKeyboard() < 0)
            break;

        sprite.setPosition(point.x, point.y);

        window.draw(sprite);
        window.display();
    }

    return 0;
}
