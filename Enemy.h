#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy
{
private:
	//enemy speed
	const float	BLOATER_SPEED = 40;
	const float	CHASER_SPEED = 80;
	const float CRAWLER_SPEED = 20;

	//enemy health
	const float	BLOATER_HEALTH = 5;
	const float	CHASER_HEALTH = 1;
	const float CRAWLER_HEALTH = 3;

	//vary speed
	const int MAX_VARIANCE = 30;
	const int OFFSET = 101 - MAX_VARIANCE;

	Vector2f m_pos;

	Sprite m_sprite;

	float m_speed;

	float m_health;

	bool m_alive;

public:
	//when a zombie is hit by the player
	bool hit();
	bool isAlive();
	void spawn(float startX, float startY, int type, int seed);
	FloatRect getPos();
	Sprite getSprite();
	void update(float elapsedTime, Vector2f playerLocation);

};
