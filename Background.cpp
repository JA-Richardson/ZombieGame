#include <SFML/Graphics.hpp>
#include "ZombieGame.h"


int createBackground(VertexArray& rVA, IntRect arena)
{
	//rVA is the same as the background in the main func
	const int TILE_SIZE = 50;
	const int TILE_TYPE = 3;
	const int VERTS_IN_QUAD = 4;

	int worldWidth = arena.width / TILE_SIZE;
	int worldHeight = arena.height / TILE_SIZE;

	//type of primitive being used
	rVA.setPrimitiveType(Quads);
	//size of array
	rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);

	int currentVert = 0;

	for (int w = 0; w < worldWidth; w++)
	{
		for (int h = 0; h < worldHeight; h++)
		{
			rVA[currentVert + 0].position = Vector2f(w * TILE_SIZE, h * TILE_SIZE);

			rVA[currentVert + 1].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);

			rVA[currentVert + 2].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);

			rVA[currentVert + 3].position = Vector2f((w * TILE_SIZE), (h * TILE_SIZE) + TILE_SIZE);

			if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1)
			{
				rVA[currentVert + 0].texCoords = Vector2f(0, 0 + TILE_TYPE * TILE_SIZE);

				rVA[currentVert + 1].texCoords = Vector2f(TILE_SIZE, 0 + TILE_TYPE * TILE_SIZE);

				rVA[currentVert + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + TILE_TYPE * TILE_SIZE);

				rVA[currentVert + 3].texCoords = Vector2f(0, TILE_SIZE + TILE_TYPE * TILE_SIZE);
			}
			else
			{
				srand((int)time(0) + h * w - h);
				int mOrG = (rand() % TILE_TYPE);
				int verticalOffset = mOrG * TILE_SIZE;

				rVA[currentVert + 0].texCoords = Vector2f(0, 0 + verticalOffset);

				rVA[currentVert + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);

				rVA[currentVert + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);

				rVA[currentVert + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

			}

			currentVert = currentVert + VERTS_IN_QUAD;
		}
	}

	return TILE_SIZE;
}