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

    // Trees

    sf::Texture treeTex;
    treeTex.loadFromFile("resources/tree.png");

    sf::Sprite trees[8];
    trees[0].setPosition(50, 60);
    trees[1].setPosition(600, 150);
    trees[2].setPosition(630, 456);
    trees[3].setPosition(300, 600);
    trees[4].setPosition(720, 40);
    trees[5].setPosition(460, 500);
    trees[6].setPosition(20, 370);
    trees[7].setPosition(340, 240);

    for(int c = 0; c < 8; c++)
    {
        trees[c].setTexture(treeTex);
        trees[c].setScale(3, 3);
    }

    // Stones

    sf::Texture stoneTex;
    stoneTex.loadFromFile("resources/stone.png");

    sf::Sprite stones[3];
    stones[0].setPosition(304, 64);
    stones[1].setPosition(664, 304);
    stones[2].setPosition(180, 300);

    for(int c = 0; c < 3; c++)
    {
        stones[c].setTexture(stoneTex);
        stones[c].setScale(3, 3);
    }

    // Player

    sf::Texture playerTex;
    playerTex.loadFromFile("resources/player.png");

    sf::Sprite player;
    player.setTexture(playerTex);
    player.setPosition(400, 300);
    player.setScale(3, 3);

    float playerMovementSpeed = 200.0;
    sf::Clock playerMovementClock;

    // Game loop

    sf::Event event;

    while(win.isOpen())
    {
        while(win.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                win.close();
        }

        // Player movements

        sf::Vector2f trans;
        float mouv = playerMovementClock.getElapsedTime().asSeconds() * playerMovementSpeed;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            trans.y -= mouv;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            trans.y += mouv;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            trans.x -= mouv;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            trans.x += mouv;

        player.setPosition(player.getPosition().x+trans.x, player.getPosition().y+trans.y);
        playerMovementClock.restart();

        // Collision testing

        for(int c=0; c < 8; c++)
        {
            if(player.getGlobalBounds().intersects(trees[c].getGlobalBounds()))
                player.setPosition(player.getPosition().x-trans.x, player.getPosition().y-trans.y);
        }
        for(int c=0; c < 3; c++)
        {
            if(player.getGlobalBounds().intersects(stones[c].getGlobalBounds()))
                player.setPosition(player.getPosition().x-trans.x, player.getPosition().y-trans.y);
        }

        // Rendering

        win.clear();

        win.draw(grass);

        for(int c = 0; c < 10; c++)
            win.draw(dirtTiles[c]);

        for(int c = 0; c < 8; c++)
            win.draw(trees[c]);

        for(int c = 0; c < 3; c++)
            win.draw(stones[c]);

        win.draw(player);

        win.display();
    }

    return 0;
}
