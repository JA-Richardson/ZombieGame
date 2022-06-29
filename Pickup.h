#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Pickup
{
private:
	const int HEALTH_START = 50;
	const int AMMO_START = 12;
	const int START_WAIT_TIME = 10;
	const int START_SECONDS_TO_LIVE = 5;

	Sprite m_Sprite;
	IntRect m_Arena;
	int m_Value;
	//1 = health, 2 = ammo
	int m_Type;

	bool m_Spawned;
	float m_SecondsSinceSpawn;
	float m_SecondsSinceDespawn;
	float m_SecondsToLive;
	float m_SecondsToWait;//how long pickup remains despawned

public:

	Pickup(int type);//constructor, takes one arg to initialise the pickup type

	void setArena(IntRect arena);//takes an intrect to know where the pickup can spawn
	void spawn();
	FloatRect getPosition();
	Sprite getSprite();
	void update(float elapsedTime);
	bool isSpawned();
	int collected();//used during collision with played to prepare respawn
	void upgrade();
};

