#include "Map.h"
#include "Define.h"

void Map::Draw()
{
	for (int i = 0; i < SIZEMAP; i++)
	{
		for (int j = 0; j < SIZEMAP; j++)
		{
			cases[i * SIZEMAP + j].draw(i, j);
		}
	}
}
