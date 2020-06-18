#include "Unit.h"
#include "Define.h"
#include "Node.h"

#include <float.h>
#include <iostream>

void Unit::MoveAI(Camera2D& camera, Vector2& CursorCamPos, Map map)
{
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		QXvec2 ClicPosition = { CursorCamPos.x / camera.zoom + camera.target.x, CursorCamPos.y / camera.zoom + camera.target.y };
		int iSuperieur = 0;
		int jSuperieur = 0;
		while (iSuperieur * SIZECASE < ClicPosition.x)
				iSuperieur++;

		while (jSuperieur * SIZECASE < ClicPosition.y)
			jSuperieur++;

		SearchPath(iSuperieur-1, jSuperieur-1, map);

		GoalNode = 0;

		if (pathNode.size() != 0)
		{
			GoalPos.x = pathNode[0]->i* SIZECASE + SIZECASE / 2;
			GoalPos.y = pathNode[0]->j * SIZECASE + SIZECASE / 2;
		}
		
	}

	if (pathNode.size() != 0 && GoalNode != pathNode.size()-1)
	{
		if ((GoalPos - Pos).Length() <= 10)
		{
			Pos = GoalPos;
			GoalNode++;
			GoalPos.x = pathNode[GoalNode]->i * SIZECASE + SIZECASE / 2;
			GoalPos.y = pathNode[GoalNode]->j * SIZECASE + SIZECASE / 2;
		}
	}

	if ((GoalPos - Pos).Length() > 10)
		Pos = Pos + (GoalPos - Pos).Normalize() * 10;
}

void Unit::CalcPositionNode(int& i, int& j, Map map)
{
	while (i * SIZECASE < Pos.x)
		i++;

	while (j * SIZECASE < Pos.y)
		j++;

	i--;
	j--;
}

void Unit::SearchPath(unsigned int iDest, unsigned int jDest, Map map)
{
	pathNode.clear();

	Node* destinationNode = &map.cases[iDest * SIZEMAP + jDest];
	std::cout << "SearchPath" << std::endl;
	int StartingPos[2] = { 0,0 };
	CalcPositionNode(StartingPos[0], StartingPos[1], map);
	AStarNode* startingNode = new AStarNode(StartingPos[0], StartingPos[1], nullptr);

	AStarList ListAstar;
	ListAstar.StartingNode = startingNode;
	ListAstar.OpenList.push_back(startingNode);

	AStarNode* DestinationNode = new AStarNode(iDest, jDest, nullptr);
	if (map.cases[(DestinationNode->i) * SIZEMAP + DestinationNode->j].state == State::OBSTACLE)
		TakeNearDestinationNode(DestinationNode, map);
	if (DestinationNode->i != StartingPos[0] || DestinationNode->j != StartingPos[1])
		NextNode(startingNode, DestinationNode, ListAstar, map);
}

void Unit::TakeNearDestinationNode(AStarNode* DestinationNode, Map map)
{
	bool isChanged = false; int difference = 1;
	while (!isChanged)
	{
		if (DestinationNode->i != difference && map.cases[(DestinationNode->i - difference) * SIZEMAP + DestinationNode->j].state == State::WALKABLE)
		{
			DestinationNode->i = DestinationNode->i - difference;
			isChanged = true;
		}
		else if (DestinationNode->i != SIZEMAP - difference && map.cases[(DestinationNode->i + difference) * SIZEMAP + DestinationNode->j].state == State::WALKABLE)
		{
			DestinationNode->i = DestinationNode->i + difference;
			isChanged = true;
		}
		else if (DestinationNode->j != difference && map.cases[(DestinationNode->i) * SIZEMAP + DestinationNode->j - difference].state == State::WALKABLE)
		{
			DestinationNode->j = DestinationNode->j - difference;
			isChanged = true;
		}
		else if (DestinationNode->j != SIZEMAP - difference && map.cases[(DestinationNode->i) * SIZEMAP + DestinationNode->j + difference].state == State::WALKABLE)
		{
			DestinationNode->j = DestinationNode->j + difference;
			isChanged = true;
		}
		else if (DestinationNode->i != SIZEMAP - difference && DestinationNode->j != difference && map.cases[(DestinationNode->i + 1) * SIZEMAP + DestinationNode->j - 1].state == State::WALKABLE)
		{
			DestinationNode->i = DestinationNode->i + difference;
			DestinationNode->j = DestinationNode->j - difference;
			isChanged = true;
		}
		else if (DestinationNode->i != SIZEMAP - difference && DestinationNode->j != SIZEMAP - difference && map.cases[(DestinationNode->i + 1) * SIZEMAP + DestinationNode->j + 1].state == State::WALKABLE)
		{
			DestinationNode->i = DestinationNode->i + difference;
			DestinationNode->j = DestinationNode->j + difference;
			isChanged = true;
		}
		else if (DestinationNode->i != difference && DestinationNode->j != difference && map.cases[(DestinationNode->i - 1) * SIZEMAP + DestinationNode->j - 1].state == State::WALKABLE)
		{
			DestinationNode->i = DestinationNode->i - difference;
			DestinationNode->j = DestinationNode->j - difference;
			isChanged = true;
		}
		else if (DestinationNode->i != difference && DestinationNode->j != SIZEMAP - difference && map.cases[(DestinationNode->i - 1) * SIZEMAP + DestinationNode->j + 1].state == State::WALKABLE)
		{
			DestinationNode->i = DestinationNode->i - difference;
			DestinationNode->j = DestinationNode->j + difference;
			isChanged = true;
		}
		difference++;
	}
}

void Unit::TestAstarNode(AStarNode* ParentNode, AStarNode* node, AStarList& ListAstar, std::vector<AStarNode*>& neighbourNode)
{
	neighbourNode.push_back(node);
	std::list<AStarNode*>::iterator itOpenList = std::find(ListAstar.OpenList.begin(), ListAstar.OpenList.end(), node);
	if (itOpenList == ListAstar.OpenList.end())
	{
		ListAstar.OpenList.push_back(node);
	}
}

void Unit::TestSideNode(AStarNode* ParentNode, std::vector<AStarNode*>& neighbourNode, AStarList& ListAstar, Map map, bool& right, bool& left, bool& down, bool& up)
{
	if (ParentNode->i != 0 && map.cases[(ParentNode->i - 1) * SIZEMAP + ParentNode->j].state == State::WALKABLE)
	{
		if (!ListAstar.CheckNodeInCloseList(ParentNode->i - 1, ParentNode->j))
		{
			AStarNode* node = ListAstar.CheckNodeInOpenList(ParentNode->i - 1, ParentNode->j);
			if (!node)
				node = new AStarNode(ParentNode->i - 1, ParentNode->j, ParentNode);
			TestAstarNode(ParentNode, node, ListAstar, neighbourNode);
			left = true;
		}
	}
	if (ParentNode->i != SIZEMAP - 1 && map.cases[(ParentNode->i + 1) * SIZEMAP + ParentNode->j].state == State::WALKABLE)
	{
		if (!ListAstar.CheckNodeInCloseList(ParentNode->i + 1, ParentNode->j))
		{
			AStarNode* node = ListAstar.CheckNodeInOpenList(ParentNode->i + 1, ParentNode->j);
			if (!node)
				node = new AStarNode(ParentNode->i + 1, ParentNode->j, ParentNode);
			TestAstarNode(ParentNode, node, ListAstar, neighbourNode);
			right = true;
		}
	}
	if (ParentNode->j != 0 && map.cases[(ParentNode->i) * SIZEMAP + ParentNode->j - 1].state == State::WALKABLE)
	{
		if (!ListAstar.CheckNodeInCloseList(ParentNode->i, ParentNode->j - 1))
		{
			AStarNode* node = ListAstar.CheckNodeInOpenList(ParentNode->i, ParentNode->j-1);
			if (!node)
				node = new AStarNode(ParentNode->i, ParentNode->j - 1, ParentNode);
			TestAstarNode(ParentNode, node, ListAstar, neighbourNode);
			up = true;
		}
	}
	if (ParentNode->j != SIZEMAP - 1 && map.cases[(ParentNode->i) * SIZEMAP + ParentNode->j + 1].state == State::WALKABLE)
	{
		if (!ListAstar.CheckNodeInCloseList(ParentNode->i, ParentNode->j + 1))
		{
			AStarNode* node = ListAstar.CheckNodeInOpenList(ParentNode->i, ParentNode->j + 1);
			if (!node)
				node = new AStarNode(ParentNode->i, ParentNode->j + 1, ParentNode);
			TestAstarNode(ParentNode, node, ListAstar, neighbourNode);
			down = true;
		}
	}
}

void Unit::TestDiagonaleNode(AStarNode* ParentNode, std::vector<AStarNode*>& neighbourNode, AStarList& ListAstar, Map map, bool& right, bool& left, bool& down, bool& up)
{
	if (right && up && map.cases[(ParentNode->i + 1) * SIZEMAP + ParentNode->j - 1].state == State::WALKABLE)
	{
		if (!ListAstar.CheckNodeInCloseList(ParentNode->i + 1, ParentNode->j - 1))
		{
			AStarNode* node = ListAstar.CheckNodeInOpenList(ParentNode->i+1, ParentNode->j - 1);
			if (!node)
				node = new AStarNode(ParentNode->i + 1, ParentNode->j - 1, ParentNode);
			TestAstarNode(ParentNode, node, ListAstar, neighbourNode);
		}
	}
	if (right && down && map.cases[(ParentNode->i + 1) * SIZEMAP + ParentNode->j + 1].state == State::WALKABLE)
	{
		if (!ListAstar.CheckNodeInCloseList(ParentNode->i + 1, ParentNode->j + 1))
		{
			AStarNode* node = ListAstar.CheckNodeInOpenList(ParentNode->i + 1, ParentNode->j + 1);
			if (!node)
				node = new AStarNode(ParentNode->i + 1, ParentNode->j + 1, ParentNode);
			TestAstarNode(ParentNode, node, ListAstar, neighbourNode);
		}
	}
	if (left && up && map.cases[(ParentNode->i - 1) * SIZEMAP + ParentNode->j - 1].state == State::WALKABLE)
	{
		if (!ListAstar.CheckNodeInCloseList(ParentNode->i - 1, ParentNode->j - 1))
		{
			AStarNode* node = ListAstar.CheckNodeInOpenList(ParentNode->i - 1, ParentNode->j - 1);
			if (!node)
				node = new AStarNode(ParentNode->i - 1, ParentNode->j - 1, ParentNode);
			TestAstarNode(ParentNode, node, ListAstar, neighbourNode);
		}
	}
	if (left && down && map.cases[(ParentNode->i - 1) * SIZEMAP + ParentNode->j + 1].state == State::WALKABLE)
	{
		if (!ListAstar.CheckNodeInCloseList(ParentNode->i - 1, ParentNode->j + 1))
		{
			AStarNode* node = ListAstar.CheckNodeInOpenList(ParentNode->i - 1, ParentNode->j + 1);
			if (!node)
				node = new AStarNode(ParentNode->i - 1, ParentNode->j + 1, ParentNode);
			TestAstarNode(ParentNode, node, ListAstar, neighbourNode);
		}
	}
}

void Unit::ComputePath(AStarNode* DestNode)
{
	if (DestNode->ParentNode != nullptr)
		ComputePath(DestNode->ParentNode);

	pathNode.push_back(DestNode);
}

void Unit::NextNode(AStarNode* ParentNode, AStarNode* DestinationNode, AStarList& ListAstar, Map map)
{
	ListAstar.OpenList.remove(ParentNode);
	ListAstar.CloseList.push_back(ParentNode);

	bool right, left, up, down;
	right = left = up = down = false;

	std::vector<AStarNode*> neighbourNode;

	TestSideNode(ParentNode, neighbourNode, ListAstar, map, right, left, down, up);
	TestDiagonaleNode(ParentNode, neighbourNode, ListAstar, map, right, left, down, up);
	
	float MinimalF = FLT_MAX; int nextNode = 0;
	for (int i = 0; i < neighbourNode.size(); i++)
	{
		if (neighbourNode[i]->i == DestinationNode->i && neighbourNode[i]->j == DestinationNode->j)
		{
			ComputePath(neighbourNode[i]);
			return;
		}
		float G = (ParentNode->PositionInWorld - neighbourNode[i]->PositionInWorld).SqrLength();
		float H = (DestinationNode->PositionInWorld - neighbourNode[i]->PositionInWorld).SqrLength();

		neighbourNode[i]->Quality = G + H;

		if (neighbourNode[i]->Quality < MinimalF)
		{
			MinimalF = neighbourNode[i]->Quality; 
			nextNode = i;
		}
	}
	if (neighbourNode.size() == 0)
	{
		if (ListAstar.OpenList.size() == 0)
		{
			TakeNearDestinationNode(DestinationNode, map);
			ListAstar.RestartList();
			if (ListAstar.CounterRestart > MAX_RESTART_PATH)
			NextNode(ListAstar.StartingNode, DestinationNode, ListAstar, map);
		}
		else
			NextNode(ListAstar.TakeBestQualityInOpenList(), DestinationNode, ListAstar, map);
	}
	else
		NextNode(neighbourNode[nextNode], DestinationNode, ListAstar, map);
}

void Unit::Draw()
{
	DrawRectangle(Pos.x - SIZECASE / 4, Pos.y - SIZECASE / 4, SIZECASE / 2, SIZECASE / 2, GREEN);
}