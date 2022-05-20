#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;
int main()
{
    //game states
    enum class State{PAUSED, LEVEL_UP, GAME_OVER, PLAYING};
    //game starts in this state
    State state = State::GAME_OVER;
    //window setup
    Vector2f screenResolution;
    screenResolution.x = VideoMode::getDesktopMode().width;
    screenResolution.y = VideoMode::getDesktopMode().height;
    RenderWindow window(VideoMode(screenResolution.x, screenResolution.y), "SFML works!");
    //view that follows the player
    View mainView(sf::FloatRect(0, 0, screenResolution.x, screenResolution.y));
    //timing
    Clock clock;
    Time gameTime;

    Vector2f mouseWorldPos;
    Vector2i mouseScreenPos;

    Player player;

    IntRect arena;

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
                int tileSize = 50;
                player.spawn(arena, screenResolution, tileSize);
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
            player.update(deltaTimeAsSeconds, Mouse::getPosition());
            Vector2f playerPos(player.getCentre());
            mainView.setCenter(player.getCentre());
        }
        //draw scene
        if (state == State::PLAYING)
        {
            window.clear();
            window.setView(mainView);
            window.draw(player.getSprite());
        }
        if (state == State::LEVEL_UP)
        {
        }
        if (state == State::PAUSED)
        {
        }
        if (state == State::GAME_OVER)
        {
        }
        window.display();
        
    }//end game loop

     return 0;
}