#include "main.hpp"

int main(int argc, const char **argv)
{
    Window window;

	sf::RenderTexture test;
	sf::Vector2u dimension = window.getSize();
	test.create(dimension.x, dimension.y);
	//sf::Uint8 pixel[4] = {255, 255, 255, 255};
	//test.update(pixel, 1, 1, 100, 100);
	//test.setSmooth(true); //Not sure

	sf::RectangleShape dot(sf::Vector2f(1, 1));
	dot.setFillColor(sf::Color(255, 255, 255, 255));
	dot.setPosition(100, 100);
	test.draw(dot);
	dot.setPosition(200, 200);
	test.draw(dot);
	test.display();

	sf::Sprite sprite(test.getTexture());

	window.clear();
	window.draw(sprite);
	window.display();

    sf::Event event;
    while (window.waitEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                window.close();
                break;
        }
    }

    return 0;
}
