#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;

	//player position
	Vector2f m_pos;

	//player sprite
	Sprite m_sprite;

	//player texture
	Texture m_texture;

	//screen resolution
	Vector2f m_resolution;

	//arena size
	IntRect m_arena;

	//tile size
	int m_tile;

	//direction of movement
	bool m_up;
	bool m_down;
	bool m_left;
	bool m_right;

	//current health and max health
	int m_health;
	int m_maxHealth;

	//when was the player last hit
	Time m_lastHit;

	//speed in pixels per second
	float m_speed;

public:

	Player();

	void spawn(IntRect arena, Vector2f resolution, int tileSize);

	//void resetPlayerStats();

	//handles player being hit
	bool hit(Time timeHit);
	
	//when was player last hit
	Time getLastHitTime();

	//where is player
	FloatRect getPosition();

	//get centre of player
	Vector2f getCentre();

	//player angle
	float getRotation();

	//send copy of sprite to main
	Sprite getSprite();

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();

	void update(float elapsedTime, Vector2i mousePos);

	//increases player speed
	void upgradeSpeed();

	//increases player health
	void upgradeHealth();

	//Increases max health player can have
	void increaseHealth(int amount);

	//currenty health
	int getHealth();
};

