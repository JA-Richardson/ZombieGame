#include "ZombieGame.h"
#include "Enemy.h"

Enemy* createHorde(int numEnemies, IntRect arena)
{
	//array of enemies
	Enemy* enemies = new Enemy[numEnemies];

	int maxY = arena.height - 20;
	int minY = arena.top + 20;

	int maxX = arena.width - 20;
	int minX = arena.left + 20;

	for (int i = 0; i < numEnemies; i++)
	{
		srand((int)time(0) * i);
		int side = (rand() % 4);
		float x, y;
		//arena side the enemies spawns on, random positions
		switch (side)
		{
		case 0:
			//left
			x = minX;
			y = (rand() % maxY) + minY;
			break;
		case 1:
			//right
			x = maxX;
			y = (rand() % maxY) + minY;
			break;
		case 2:
			//top
			x = (rand() % maxX) + minX;
			y = minY;
			break;
		case 3:
			//bottom
			x = (rand() % maxX) + minX;
			y = maxY;
			break;
		}
		//rand num seed to choose enemy type
		srand((int)time(0) * i * 2);
		int type = (rand() % 3);
		//spawns an enemy into the array
		enemies[i].spawn(x, y, type, i);
	}
	return enemies;
	
}