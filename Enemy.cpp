#include "Enemy.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>

using namespace std;

void Enemy::spawn(float startX, float startY, int type, int seed)
{
	switch (type)
	{
	case 0:
		//Bloater
		m_sprite = Sprite(TextureHolder::GetTexture("graphics/bloater.png"));
		m_speed = BLOATER_SPEED;
		m_health = BLOATER_HEALTH;
		break;

	case 1:
		//Chaser 
		m_sprite = Sprite(TextureHolder::GetTexture("graphics/chaser.png"));
		m_speed = CHASER_SPEED;
		m_health = CHASER_HEALTH;
		break;

	case 2:
		//Crawler
		m_sprite = Sprite(TextureHolder::GetTexture("graphics/crawler.png"));
		m_speed = CRAWLER_SPEED;
		m_health = CRAWLER_HEALTH;
		break;
	}

	//make each enemy speed unique
	srand((int)time(0) * seed);

	float modifier = (rand() % MAX_VARIANCE + OFFSET);

	modifier /= 100;
	m_speed *= modifier;

	m_pos.x = startX;
	m_pos.y = startY;

	m_sprite.setOrigin(25, 25);
	m_sprite.setPosition(m_pos);
}

bool Enemy::hit()
{
	m_health--;
	if (m_health < 0)//dead
	{
		m_alive = false;
		m_sprite.setTexture(TextureHolder::GetTexture("graphics/blood.png"));
		return true;
	}
	return false;//not dead
}

bool Enemy::isAlive()
{
	return m_alive;
}

FloatRect Enemy::getPos()
{
	return m_sprite.getGlobalBounds();
}

Sprite Enemy::getSprite()
{
	return m_sprite;
}

void Enemy::update(float elapsedTime, Vector2f playerLocation)
{
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;
	//checks to see if enemy is below, left, right or above player and moves them accordingly
	if (playerX > m_pos.x)
	{
		m_pos.x = m_pos.x + m_speed * elapsedTime;
	}
	if (playerY > m_pos.y)
	{
		m_pos.y = m_pos.y + m_speed * elapsedTime;
	}
	if (playerX < m_pos.x)
	{
		m_pos.x = m_pos.x -	m_speed * elapsedTime;
	}
	if (playerY < m_pos.y)
	{
		m_pos.y = m_pos.y - m_speed * elapsedTime;
	}

	m_sprite.setPosition(m_pos);
	//sets the enemy to be facing the player
	float angle = (atan2(playerY - m_pos.y, playerX - m_pos.x) * 180) / 3.141;
	m_sprite.setRotation(angle);
}