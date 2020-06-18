#include "Node.h"

void Node::draw(int i, int j)
{
	if (state == State::WALKABLE)
		DrawRectangleLines(i * SIZECASE, j * SIZECASE, SIZECASE, SIZECASE, MAROON);
	else
		DrawRectangle(i * SIZECASE, j * SIZECASE, SIZECASE, SIZECASE, BLACK);
}