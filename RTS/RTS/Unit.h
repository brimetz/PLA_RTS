#pragma once

#include "raylib.h"
#include "Vec2.h"
#include "Map.h"
#include <list>

struct AStarNode
{
	int i;
	int j;
	QXvec2 PositionInWorld;
	AStarNode* ParentNode = nullptr;
	float Quality = FLT_MAX;

	AStarNode(int x, int y)
	{
		i = x; j = y;
		PositionInWorld = { (float)(SIZECASE / 2 + i * SIZECASE), (float)(SIZECASE / 2 + j * SIZECASE) };
	}

	AStarNode(int x, int y, AStarNode* ptr)
	{
		i = x; j = y; ParentNode = ptr;
		PositionInWorld = { (float)(SIZECASE / 2 + i * SIZECASE), (float)(SIZECASE / 2 + j * SIZECASE) };
	}
};

struct AStarList
{
	std::list<AStarNode*> CloseList;
	std::list<AStarNode*> OpenList;

	AStarNode* StartingNode;

	int CounterRestart = 0;

	bool CheckNodeInCloseList(int i, int j)
	{
		for (auto it = CloseList.begin(); it != CloseList.end(); ++it)
		{
			if ((*it)->i == i && (*it)->j == j)
				return true;
		}
		return false;
	}

	AStarNode* CheckNodeInOpenList(int i, int j)
	{
		for (auto it = OpenList.begin(); it != OpenList.end(); ++it)
		{
			if ((*it)->i == i && (*it)->j == j)
				return (*it);
		}
		return nullptr;
	}

	AStarNode* TakeBestQualityInOpenList()
	{
		float BestQuality = FLT_MAX; AStarNode* BestNode = nullptr;
		for (auto it = OpenList.begin(); it != OpenList.end(); ++it)
		{
			if (BestQuality > (*it)->Quality)
			{
				BestQuality = (*it)->Quality;
				BestNode = *it;
			}
		}
		return BestNode;
	}

	void RestartList()
	{
		for (auto it = CloseList.begin(); it != CloseList.end();)
			it = CloseList.erase(it);
		CloseList.clear();
		for (auto it = OpenList.begin(); it != OpenList.end();)
			it = OpenList.erase(it);
		OpenList.clear();

		OpenList.push_back(StartingNode);

		CounterRestart++;
	}
};

struct Unit
{
	QXvec2 Pos = { 300,300 };
	QXvec2 vecDir = { 0,0 };
	QXvec2 GoalPos = { 300,300 };

	int GoalNode = -1;
	std::vector<AStarNode*> pathNode;

	void CalcPositionNode(int& i, int& j, Map map);
	void MoveAI(Camera2D& camera, Vector2& CursorCamPos, Map map);

	void SearchPath(unsigned int iDest, unsigned int jDest, Map map);
	void NextNode(AStarNode* ParentNode, AStarNode* DestinationNode, AStarList& ListAstar,  Map map);
	void TestAstarNode(AStarNode* ParentNode, AStarNode* node, AStarList& ListAstar, std::vector<AStarNode*>& neighbourNode);
	void TestSideNode(AStarNode* ParentNode, std::vector<AStarNode*>& neighbourNode, AStarList& ListAstar, Map map, bool& right, bool& left, bool& down, bool& up);
	void TestDiagonaleNode(AStarNode* ParentNode, std::vector<AStarNode*>& neighbourNode, AStarList& ListAstar, Map map, bool& right, bool& left, bool& down, bool& up);

	void TakeNearDestinationNode(AStarNode* DestinationNode, Map map);

	void ComputePath(AStarNode* DestNode);

	void Draw();
};

