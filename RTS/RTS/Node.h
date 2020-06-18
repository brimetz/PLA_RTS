#pragma once

#include "raylib.h"
#include "Vec2.h"
#include "Define.h"

enum class State
{
	WALKABLE,
	OBSTACLE
};

struct Node
{
	State state = State::WALKABLE;

	void draw(int i, int j);
};

