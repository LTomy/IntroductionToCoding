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

    // Dirt tiles

    sf::Texture dirtTex;
    dirtTex.loadFromFile("resources/dirt.png");

    sf::Sprite dirtTiles[10];
    dirtTiles[0].setPosition(300, 60);
    dirtTiles[1].setPosition(660, 300);
    dirtTiles[2].setPosition(390, 480);
    dirtTiles[3].setPosition(660, 60);
    dirtTiles[4].setPosition(720, 420);
    dirtTiles[5].setPosition(180, 300);
    dirtTiles[6].setPosition(60, 180);
    dirtTiles[7].setPosition(60, 420);
    dirtTiles[8].setPosition(240, 420);
    dirtTiles[9].setPosition(480, 120);

    for(int c = 0; c < 10; c++)
    {
        dirtTiles[c].setTexture(dirtTex);
        dirtTiles[c].setScale(5, 5);
    }

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

        for(int c = 0; c < 10; c++)
            win.draw(dirtTiles[c]);

        win.display();
    }

    return 0;
}

