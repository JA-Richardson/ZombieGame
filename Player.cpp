#include "Player.h"
#include "TextureHolder.h"

Player::Player()
{
	m_speed = START_SPEED;
	m_health = START_HEALTH;
	m_maxHealth = START_HEALTH;

	//texture for the sprite
	m_sprite = Sprite(TextureHolder::GetTexture("graphics/player.png"));

	//sets sprite origin to centre
	m_sprite.setOrigin(25, 25);
}

void Player::spawn(IntRect arena, Vector2f resolution, int tileSize)
{
	//spawns player in middle of arena
	m_pos.x = arena.width / 2;
	m_pos.y = arena.width / 2;

	//copies arena to m_arena
	m_arena.left = arena.left;
	m_arena.width = arena.width;
	m_arena.top = arena.top;
	m_arena.height = arena.height;

	//remember size of tile in the arena
	m_tile = tileSize;

	//stores resolution
	m_resolution.x = resolution.x;
	m_resolution.y = resolution.y;

}

//void Player::resetPlayerStats()
//{
//	m_speed = START_SPEED;
//	m_health = START_HEALTH;
//	m_maxHealth = START_HEALTH;
//}

bool Player::hit(Time timeHit)
{
	if (timeHit.asMilliseconds() - m_lastHit.asMilliseconds() > 200)
	{
		m_lastHit = timeHit;
		m_health -= 10;
		return true;
	}
	else
	{
		return false;
	}
}

Time Player::getLastHitTime()
{
	return m_lastHit;
}

FloatRect Player::getPosition()
{
	return m_sprite.getGlobalBounds();
}

Vector2f Player::getCentre()
{
	return m_pos;
}

float Player::getRotation()
{
	return m_sprite.getRotation();
}

Sprite Player::getSprite()
{
	return m_sprite;
}

void Player::moveLeft()
{
	m_left = true;
}

void Player::moveRight()
{
	m_right = true;
}

void Player::moveUp()
{
	m_up = true;
}

void Player::moveDown()
{
	m_down = true;
}

void Player::stopLeft()
{
	m_left = false;
}

void Player::stopRight()
{
	m_right = false;
}

void Player::stopUp()
{
	m_up = false;
}

void Player::stopDown()
{
	m_down = false;
}

void Player::update(float elapsedTime, Vector2i mousePos)
{
	if (m_up)
	{
		m_pos.y -= m_speed * elapsedTime;
	}
	if (m_down)
	{
		m_pos.y += m_speed * elapsedTime;
	}
	if (m_right)
	{
		m_pos.x += m_speed * elapsedTime;
	}
	if (m_left)
	{
		m_pos.x -= m_speed * elapsedTime;
	}

	m_sprite.setPosition(m_pos);

	//keeps player in arena
	if (m_pos.x > m_arena.width - m_tile)
	{
		m_pos.x = m_arena.width - m_tile;
	}
	if (m_pos.x < m_arena.left + m_tile)
	{
		m_pos.x = m_arena.left + m_tile;
	}
	if (m_pos.y > m_arena.height - m_tile)
	{
		m_pos.y = m_arena.height - m_tile;
	}
	if (m_pos.y < m_arena.top + m_tile)
	{
		m_pos.y = m_arena.top + m_tile;
	}

	//calc player angle
	float angle = (atan2(mousePos.y - m_resolution.y / 2, mousePos.x - m_resolution.x / 2) * 180) / 3.141;
	m_sprite.setRotation(angle);
}

void Player::upgradeSpeed()
{
	m_speed += (START_SPEED * .2);
}

void Player::upgradeHealth()
{
	m_maxHealth += (START_HEALTH * .2);
}

void Player::increaseHealth(int amount)
{
	m_health += amount;
	if (m_health > m_maxHealth)
	{
		m_health = m_maxHealth;
	}
}

//int Player::getHealth()
//{
//	return m_health;
//}
