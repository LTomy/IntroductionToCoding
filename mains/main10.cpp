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
    sf::Texture playerAttackingTex;
    playerAttackingTex.loadFromFile("resources/playerAttacking.png");

    sf::Sprite player;
    player.setTexture(playerTex);
    player.setPosition(400, 300);
    player.setScale(3, 3);

    float playerMovementSpeed = 200.0;
    sf::Clock playerMovementClock;
    sf::Clock playerAttackClock;

    int playerGoldAmount = 0, playerPotionAmount = 0, playerHealthAmount = 3;

    // Monsters

    sf::Texture monsterTexs[3];
    monsterTexs[0].loadFromFile("resources/monster1.png");
    monsterTexs[1].loadFromFile("resources/monster2.png");
    monsterTexs[2].loadFromFile("resources/monster3.png");

    sf::Sprite monsters[4];
    monsters[0].setPosition(500, 40);
    monsters[1].setPosition(100, 170);
    monsters[2].setPosition(400, 450);
    monsters[3].setPosition(690, 160);

    bool monstersDead[4];

    for(int c = 0; c < 4; c++)
    {
        monsters[c].setTexture(monsterTexs[0]);
        monsters[c].setScale(3, 3);
        monstersDead[c] = false;
    }

    sf::Clock monstersAnimationClock;
    sf::Clock monsterRespawnClocks[4];
    sf::Clock monsterAttackClock;
    bool isPlayerNearMonster = false;

    // Gold

    sf::Texture goldTex;
    goldTex.loadFromFile("resources/gold.png");

    sf::Sprite gold;
    gold.setTexture(goldTex);
    gold.setScale(2, 2);
    gold.setPosition(15, 10);

    sf::Font font;
    font.loadFromFile("resources/LinuxBiolinum.ttf");

    sf::Text goldAmountText;
    goldAmountText.setFont(font);
    goldAmountText.setString("0");
    goldAmountText.setFillColor(sf::Color::White);
    goldAmountText.setCharacterSize(24);
    goldAmountText.setPosition(60, 10);

    // Potions

    sf::Texture healthPotionTex;
    healthPotionTex.loadFromFile("resources/healthPotion.png");
    sf::Texture emptyVialTex;
    emptyVialTex.loadFromFile("resources/emptyVial.png");

    sf::Sprite potion;
    potion.setTexture(emptyVialTex);
    potion.setScale(2, 2);
    potion.setPosition(350, 10);

    sf::Text potionAmountText;
    potionAmountText.setFont(font);
    potionAmountText.setString("0");
    potionAmountText.setFillColor(sf::Color::White);
    potionAmountText.setCharacterSize(24);
    potionAmountText.setPosition(395, 10);

    // Health of the player

    sf::Texture heartTex;
    heartTex.loadFromFile("resources/heart.png");
    sf::Texture emptyHeartTex;
    emptyHeartTex.loadFromFile("resources/emptyHeart.png");

    sf::Sprite hearts[3];
    hearts[0].setPosition(800 - 130, 10);
    hearts[1].setPosition(800 - 90, 10);
    hearts[2].setPosition(800 - 50, 10);

    for(int c = 0; c < 3; c++)
    {
        hearts[c].setTexture(heartTex);
        hearts[c].setScale(2, 2);
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

        // Animation of the monsters

        int index = monstersAnimationClock.getElapsedTime().asMilliseconds() / 333;

        if(index > 2)
        {
            monstersAnimationClock.restart();
            index = 0;
        }

        for(int c=0; c < 4; c++)
        {
            monsters[c].setTexture(monsterTexs[index]);
        }

        // Player attacking

        if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) && playerAttackClock.getElapsedTime().asMilliseconds() > 1000)
        {
            playerAttackClock.restart();
            player.setTexture(playerAttackingTex);

            // Testing if the attack reaches a monster

            sf::FloatRect attackRect(player.getPosition()+sf::Vector2f((player.getGlobalBounds().width/4), -player.getGlobalBounds().height/3), sf::Vector2f(player.getGlobalBounds().width/4, player.getGlobalBounds().height/3));

            for(int c=0; c < 4; c++)
            {
                if(monstersDead[c] == false && attackRect.intersects(monsters[c].getGlobalBounds()))
                {
                    monstersDead[c] = true;
                    monsterRespawnClocks[c].restart();
                }
            }
        }

        if(playerAttackClock.getElapsedTime().asMilliseconds() > 1000)
            player.setTexture(playerTex);

        // Monster attacking

        bool isPlayerCurrentlyNearMonster = false;

        for(int c=0; c < 4; c++)
        {
            if(monstersDead[c] == false)
            {
                sf::FloatRect nearMonsterRect(monsters[c].getGlobalBounds());
                nearMonsterRect.left -= nearMonsterRect.width;
                nearMonsterRect.top -= nearMonsterRect.height;
                nearMonsterRect.width *= 3;
                nearMonsterRect.height *= 3;

                if(player.getGlobalBounds().intersects(nearMonsterRect))
                {
                    isPlayerCurrentlyNearMonster = true;

                    if(isPlayerNearMonster)
                    {
                        if(monsterAttackClock.getElapsedTime().asSeconds() >= 1 && playerHealthAmount > 0)
                        {
                            playerHealthAmount--;
                            monsterAttackClock.restart();

                            if(playerHealthAmount == 0)
                                hearts[0].setTexture(emptyHeartTex);
                            else if(playerHealthAmount == 1)
                                hearts[1].setTexture(emptyHeartTex);
                            else
                                hearts[2].setTexture(emptyHeartTex);
                        }
                    }
                    else
                    {
                        isPlayerNearMonster = true;
                        monsterAttackClock.restart();
                    }
                }
            }
        }

        if(isPlayerCurrentlyNearMonster == false)
            isPlayerNearMonster = false;

        // Respawn of the monsters

        for(int c=0; c < 4; c++)
        {
            if(monsterRespawnClocks[c].getElapsedTime().asSeconds() >= 8)
                monstersDead[c] = false;
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

        for(int c = 0; c < 4; c++)
        {
            if(monstersDead[c] == false)
                win.draw(monsters[c]);
        }


        win.draw(gold);
        win.draw(goldAmountText);

        win.draw(potion);
        win.draw(potionAmountText);

        for(int c = 0; c < 3; c++)
            win.draw(hearts[c]);

        win.display();
    }

    return 0;
}
