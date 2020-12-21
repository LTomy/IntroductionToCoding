#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow win(sf::VideoMode(800, 600), "Introduction to coding", sf::Style::Close);

	// Limits the framerate
    win.setVerticalSyncEnabled(true);
	
    // Grass

    sf::Texture grassTex;
    grassTex.loadFromFile("resources/grass.png");
    grassTex.setRepeated(true);

    sf::Sprite grass;
    grass.setTexture(grassTex);
    grass.setScale(5, 5);
    grass.setTextureRect(sf::IntRect(0,0,160,120));

    // Game loop

    sf::Event event;

    while(win.isOpen())
    {
        while(win.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                win.close();
        }

        win.clear();

        win.draw(grass);

        win.display();
    }

    return 0;
}

