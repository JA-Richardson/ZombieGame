#include <sstream>
#include <SFML/Graphics.hpp>
#include "ZombieGame.h"
#include "Player.h"
#include "TextureHolder.h"
#include "Bullet.h"
#include "Pickup.h"


using namespace sf;
int main()
{

    TextureHolder holder;
    //game states
    enum class State { PAUSED, LEVEL_UP, GAME_OVER, PLAYING };
    //game starts in this state
    State state = State::GAME_OVER;
    //window setup
    Vector2f screenResolution;
    screenResolution.x = VideoMode::getDesktopMode().width;
    screenResolution.y = VideoMode::getDesktopMode().height;
    RenderWindow window(VideoMode(screenResolution.x, screenResolution.y), "Window");
    //view that follows the player
    View mainView(sf::FloatRect(0, 0, screenResolution.x, screenResolution.y));
    //timing
    Clock clock;
    Time gameTime;

    Vector2f mouseWorldPos;
    Vector2i mouseScreenPos;

    Player player;

    IntRect arena;

    VertexArray background;
    Texture backgroundTex = TextureHolder::GetTexture("graphics/background_sheet.png");

    int numEnemies;
    int numEnemiesAlive;
    Enemy* enemies = NULL;

    //bullet setup
    Bullet bullet[100];
    int currentBullet = 0;
    int reserveAmmo = 24;
    int bulletsInMag = 6;
    int magSize = 6;
    float fireRate = 1;
    //when was ladt fired?
    Time lastPressed;

    window.setMouseCursorVisible(false);
    Sprite crosshairSprite;
    Texture crosshairTex = TextureHolder::GetTexture("graphics/crosshair.png");
    crosshairSprite.setTexture(crosshairTex);
    crosshairSprite.setOrigin(25,25);

    Pickup healthPickup(1);
    Pickup ammoPickup(2);

    int score = 0;
    int highScore = 0;

    //home/game over
    Sprite spriteGameOver;
    Texture texGameOver = TextureHolder::GetTexture("graphics/background.png");
    spriteGameOver.setTexture(texGameOver);
    spriteGameOver.setPosition(0, 0);

    //HUD
    View HUD(sf::FloatRect(0, 0, screenResolution.x, screenResolution.y));

    //Ammo counter sprite
    Sprite spriteAmmoIcon;
    Texture texAmmoIcon = TextureHolder::GetTexture("graphics/ammo_icon.png");
    spriteAmmoIcon.setTexture(texAmmoIcon);
    spriteAmmoIcon.setPosition(20, 980);

    //font
    Font font;
    font.loadFromFile("font/bloodcrow.ttf");

    //paused
    Text pausedText;
    pausedText.setFont(font);
    pausedText.setCharacterSize(155);
    pausedText.setFillColor(Color::White);
    pausedText.setPosition(400, 400);
    pausedText.setString("Press Enter \nto continue");

    //Game over
    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(125);
    gameOverText.setFillColor(Color::White);
    gameOverText.setPosition(250, 850);
    gameOverText.setString("Press Enter to play");

    // LEVELING up
    Text levelUpText;
    levelUpText.setFont(font);
    levelUpText.setCharacterSize(80);
    levelUpText.setFillColor(Color::White);
    levelUpText.setPosition(150, 250);
    std::stringstream levelUpStream;
    levelUpStream <<
        "1- Increased rate of fire" <<
        "\n2- Increased clip size(next reload)" <<
        "\n3- Increased max health" <<
        "\n4- Increased run speed" <<
        "\n5- More and better health pickups" <<
        "\n6- More and better ammo pickups";
    levelUpText.setString(levelUpStream.str());

    // Ammo
    Text ammoText;
    ammoText.setFont(font);
    ammoText.setCharacterSize(55);
    ammoText.setFillColor(Color::White);
    ammoText.setPosition(200, 980);

    // Score
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(55);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(20, 0);

    // High Score
    Text highScoreText;
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(55);
    highScoreText.setFillColor(Color::White);
    highScoreText.setPosition(1400, 0);
    std::stringstream s;
    s << "High Score:" << highScore;
    highScoreText.setString(s.str());

    // Zombies remaining
    Text enemiesRemainingText;
    enemiesRemainingText.setFont(font);
    enemiesRemainingText.setCharacterSize(55);
    enemiesRemainingText.setFillColor(Color::White);
    enemiesRemainingText.setPosition(1500, 980);
    enemiesRemainingText.setString("Zombies: 100");

    // Wave number
    int wave = 0;
    Text waveNumberText;
    waveNumberText.setFont(font);
    waveNumberText.setCharacterSize(55);
    waveNumberText.setFillColor(Color::White);
    waveNumberText.setPosition(1250, 980);
    waveNumberText.setString("Wave: 0");

    // Health bar
    RectangleShape healthBar;
    healthBar.setFillColor(Color::Red);
    healthBar.setPosition(450, 980);

    int framesSinceLastHUDUpdate = 0;
    int fpsMeasurementFrameInterval = 1000;

    while (window.isOpen())
    {
        //input

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Return && state == State::PLAYING)
                {
                    state == State::PAUSED;
                }

                else if (event.key.code == Keyboard::Return && state == State::PAUSED)
                {
                    state = State::PLAYING;
                    //clock restarts to avoid frame jump
                    clock.restart();
                }

                else if (event.key.code == Keyboard::Return && state == State::GAME_OVER)
                {
                    state = State::LEVEL_UP;
                }
                if (state == State::PLAYING)
                {
                    if (event.key.code == Keyboard::R)
                    {
                        if (reserveAmmo >= magSize)
                        {
                            bulletsInMag = magSize;
                            reserveAmmo -= magSize;
                        }
                        else if (reserveAmmo > 0)
                        {
                            bulletsInMag = reserveAmmo;
                            reserveAmmo = 0;
                        }
                        else
                        {

                        }
                    }
                }

            }//end poll
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        //player movement
        if (state == State::PLAYING);
        {
            if (Keyboard::isKeyPressed(Keyboard::W))
            {
                player.moveUp();
            }
            else
            {
                player.stopUp();
            }
            if (Keyboard::isKeyPressed(Keyboard::S))
            {
                player.moveDown();
            }
            else
            {
                player.stopDown();
            }
            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                player.moveLeft();
            }
            else
            {
                player.stopLeft();
            }
            if (Keyboard::isKeyPressed(Keyboard::D))
            {
                player.moveRight();
            }
            else
            {
                player.stopRight();
            }

            //Fire weapon
            if (Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (gameTime.asMilliseconds() - lastPressed.asMilliseconds() > 1000 / fireRate && bulletsInMag > 0)
                {
                    //pass player centre and crosshair to shoot func
                    bullet[currentBullet].shoot(player.getCentre().x, player.getCentre().y, mouseWorldPos.x, mouseWorldPos.y);
                    currentBullet++;
                    if (currentBullet > 99)
                    {
                        currentBullet = 0;
                    }
                    lastPressed = gameTime;
                    bulletsInMag--;
                }
            }//end firing
        }//end player movement
        //level up state
        if (state == State::LEVEL_UP)
        {
            //levelling up
            if (event.key.code == Keyboard::Num1)
            {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num2)
            {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num3)
            {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num4)
            {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num5)
            {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num6)
            {
                state = State::PLAYING;
            }
            if (state == State::PLAYING)
            {
                //prep level
                arena.width = 500;
                arena.height = 500;
                arena.left = 0;
                arena.top = 0;
                //passes vertex array be refernce to the createbackground func
                int tileSize = createBackground(background, arena);
                //spawns player in middle of arena
                player.spawn(arena, screenResolution, tileSize);
                //config for pickups
                healthPickup.setArena(arena);
                ammoPickup.setArena(arena);
                //enemies to be spawned at start
                numEnemies = 10;
                //delete allocated memory if needed
                delete[] enemies;
                enemies = createHorde(numEnemies, arena);
                numEnemiesAlive = numEnemies;
                //reset clock so no frame jump
                clock.restart();
            }
        }//end level up

        //update frames
        if (state == State::PLAYING)
        {
            Time deltaTime = clock.restart();
            gameTime += deltaTime;
            //decilam fraction of 1 from deltatime
            float deltaTimeAsSeconds = deltaTime.asSeconds();
            mouseScreenPos = Mouse::getPosition();
            //convert mouse pos to world coords of mainview
            mouseWorldPos = window.mapPixelToCoords(Mouse::getPosition(), mainView);
            crosshairSprite.setPosition(mouseWorldPos);
            player.update(deltaTimeAsSeconds, Mouse::getPosition());
            Vector2f playerPos(player.getCentre());
            mainView.setCenter(player.getCentre());
            //zombie update loop
            for (int i = 0; i < numEnemies; i++)
            {
                if (enemies[i].isAlive())
                {
                    enemies[i].update(deltaTime.asSeconds(), playerPos);
                }
            }
            //bullet update loop
            for (int i = 0; i < 100; i++)
            {
                if (bullet[i].isActive())
                {
                    bullet[i].update(deltaTimeAsSeconds);
                }
            }
            healthPickup.update(deltaTimeAsSeconds);
            ammoPickup.update(deltaTimeAsSeconds);

            //collision detection
            //have enemies been shot
            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < numEnemies; j++)
                {
                    if (bullet[i].isActive() && enemies[j].isAlive())
                    {
                        if (bullet[i].getPos().intersects(enemies[j].getPos()))
                        {
                            bullet[i].stop();

                            if (enemies[j].hit())
                            {
                                //if enemy killed
                                score += 10;
                                if (score >= highScore)
                                {
                                    highScore = score;
                                }
                                numEnemiesAlive--;
                                if (numEnemiesAlive == 0)
                                {
                                    state = State::LEVEL_UP;
                                }
                            }
                        }
                    }
                }
            }//end enemy

            //has player been hit
            for (int i = 0; i < numEnemies; i++)
            {
                if (player.getPosition().intersects
                (enemies[i].getPos()) && enemies[i].isAlive())
                {
                    if (player.hit(gameTime))
                    {

                    }
                    if (player.getHealth()<=0)
                    {
                        state = State::GAME_OVER;
                    }
                }
            }//end player hit
            //player hit hralth?
            if (player.getPosition().intersects(healthPickup.getPosition()) && healthPickup.isSpawned())
            {
                player.increaseHealth(healthPickup.collected());
            }
            //player hit ammo
            if (player.getPosition().intersects(ammoPickup.getPosition()) && ammoPickup.isSpawned())
            {
                reserveAmmo += ammoPickup.collected();
            }
            //size of hp bar
            healthBar.setSize(Vector2f(player.getHealth() * 3, 50));
            //increment frames since alst update
            framesSinceLastHUDUpdate++;
            //recalc every fpsmeasurmentframeinterval frames
            if (framesSinceLastHUDUpdate > fpsMeasurementFrameInterval)
            {
                //hud text
                std::stringstream ssAmmo;
                std::stringstream ssScore;
                std::stringstream ssHighscore;
                std::stringstream ssWave;
                std::stringstream ssEnemiesAlive;

                //ammo text
                ssAmmo << bulletsInMag << "/" << reserveAmmo;
                ammoText.setString(ssAmmo.str());
                //score text
                ssScore << "Score: " << score;
                scoreText.setString(ssScore.str());
                //high score text
                ssHighscore << "High Score: " << highScore;
                highScoreText.setString(ssHighscore.str());
                //wave text
                ssWave << "Wave: " << wave;
                waveNumberText.setString(ssWave.str());
                //enemies remaininh
                ssEnemiesAlive << "Enemies: " << numEnemiesAlive;
                enemiesRemainingText.setString(ssEnemiesAlive.str());
                framesSinceLastHUDUpdate = 0;
            }//end hud updates
        }//end updates
        //draw scene
        if (state == State::PLAYING)
        {
            window.clear();
            window.setView(mainView);
            window.draw(background, &backgroundTex); //pointer for the background
            for (int i = 0; i < numEnemies; i++)
            {
                window.draw(enemies[i].getSprite());
            }
            for (int i = 0; i < 100; i++)
            {
                if (bullet[i].isActive())
                {
                    window.draw(bullet[i].getShape());
                }
            }
            window.draw(player.getSprite());
            if (ammoPickup.isSpawned())
            {
                window.draw(ammoPickup.getSprite());
            }
            if (healthPickup.isSpawned())
            {
                window.draw(healthPickup.getSprite());
            }

            window.draw(crosshairSprite);
            window.setView(HUD);
            window.draw(spriteAmmoIcon);
            window.draw(ammoText);
            window.draw(scoreText);
            window.draw(highScoreText);
            window.draw(healthBar);
            window.draw(waveNumberText);
            window.draw(enemiesRemainingText);
        }
        if (state == State::LEVEL_UP)
        {
            window.draw(spriteGameOver);
            window.draw(levelUpText);
        }
        if (state == State::PAUSED)
        {
            window.draw(pausedText);
        }
        if (state == State::GAME_OVER)
        {
            window.draw(spriteGameOver);
            window.draw(gameOverText);
            window.draw(scoreText);
            window.draw(highScoreText);
        }
        window.display();
        
    }//end game loop
    delete[] enemies;

     return 0;
}