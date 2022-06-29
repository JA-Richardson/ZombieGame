#include "Bullet.h"

Bullet::Bullet()
{
	m_BulletShape.setSize(sf::Vector2f(10, 10));
}

void Bullet::stop()
{
	m_active = false;
}

bool Bullet::isActive()
{
	return m_active;
}

void Bullet::shoot(float startX, float startY, float xTarget, float yTarget)
{
	//tracking bullet
	m_active = true;
	m_pos.x = startX;
	m_pos.y = startY;
	//gradient of flight pathj
	float gradient = (startX - xTarget) / (startY - yTarget);
	//if gradient is less than 1 it needs to be negative
	if (gradient < 0)
	{
		gradient *= -1;
	}
	//ratio between X and Y
	float ratioXY = m_BulletSpeed / (1 + gradient);

	//set bullet "speed"
	m_BulletDistanceY = ratioXY;
	m_BulletDistanceX = ratioXY * gradient;

	//face bullet in correct direction
	if (xTarget < startX)
	{
		m_BulletDistanceX *= -1;
	}
	if (yTarget < startY)
	{
		m_BulletDistanceY *= -1;
	}

	//max range of bullet
	float range = 1000;
	m_MinX = startX - range;
	m_MaxX = startX + range;
	m_MinY = startY - range;
	m_MaxY = startY + range;

	//position bullet to be drawn
	m_BulletShape.setPosition(m_pos);
}

FloatRect Bullet::getPos()
{
	return m_BulletShape.getGlobalBounds();
}

RectangleShape Bullet::getShape()
{
	return m_BulletShape;
}

void Bullet::update(float elapsedTime)
{
	//update position variables
	m_pos.x += m_BulletDistanceX * elapsedTime;
	m_pos.y += m_BulletDistanceY * elapsedTime;

	//move bullet
	m_BulletShape.setPosition(m_pos);

	//has it gone out of range
	if (m_pos.x < m_MinX || m_pos.x > m_MaxX || m_pos.y < m_MinY || m_pos.y > m_MaxY)
	{
		m_active = false;
	}

}
