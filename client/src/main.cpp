#include "main.hpp"

int main(int argc, const char **argv)
{
	srand(time(NULL));

	Window             window;
	sf::RenderTexture  star_layers[3];
	sf::Vector2u       dimension = window.getSize();
	sf::RectangleShape dot(sf::Vector2f(1, 1));

	/* Prepare star textures */
	for (int layer = 0; layer < 3; layer++) {
		star_layers[layer].create(dimension.x, dimension.y);

		for (int i = 0; i < 500; i++) {
			int mod_color = -1 * (rand() % 100);
			dot.setFillColor(sf::Color(255 + mod_color, 255 + mod_color, 255, 100 + (rand() % 155)));
			dot.setPosition(rand() % dimension.x, rand() % dimension.y);
			star_layers[layer].draw(dot);
		}
		
		star_layers[layer].display();
	}

	/* Prepare star sprites */
	sf::Sprite star_sprites[3] = {
		sf::Sprite(star_layers[0].getTexture()),
		sf::Sprite(star_layers[1].getTexture()),
		sf::Sprite(star_layers[2].getTexture())
	};

	/* Main loop */
    sf::Event event;
	sf::Clock clock;
	int step = 0;
    while (window.isOpen()) {

		/* Event handling */
		window.pollEvent(event);
		switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
                break;
        }

		/* Star parallax animation */
		sf::Time elapsed = clock.getElapsedTime();
		if (elapsed.asMilliseconds() >= 10) {
			step++;
			clock.restart();
			if (step > 0) star_sprites[0].setPosition(star_sprites[0].getPosition().x - 1, star_sprites[0].getPosition().y);
			if (step > 1) star_sprites[1].setPosition(star_sprites[1].getPosition().x - 1, star_sprites[1].getPosition().y);
			if (step > 2) star_sprites[2].setPosition(star_sprites[2].getPosition().x - 1, star_sprites[2].getPosition().y);
			if (step > 3) step = 0;
		}

		/* Draw frame */
		window.clear();
		window.draw(star_sprites[0]);
		window.draw(star_sprites[1]);
		window.draw(star_sprites[2]);
		window.display();

		/* Avoid burning too much CPU */
		sf::sleep(sf::milliseconds(20));

    }

    return 0;
}
