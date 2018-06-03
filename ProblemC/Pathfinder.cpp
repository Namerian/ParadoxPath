/*
 * Pathfinder.cpp
 *
 *  Created on: Mar 19, 2017
 *      Author: patrick
 */

#include <cstddef>
#include <map>
#include <cmath>
#include <algorithm>
#include <vector>

#include <iostream>

#include "Pathfinder.h"
#include "Node.h"
#include "PriorityQueue.h"

int ComputeIndex(const int posX, const int posY, const int mapWidth)
{
	return posX + posY * mapWidth;
}

int ComputeRemainingCost(const int index1, const int index2, const int mapWidth)
{
	return std::abs(index2 / mapWidth - index1 / mapWidth) + std::abs(index2 % mapWidth - index1 % mapWidth);
}

//==================================================================================
//
//==================================================================================

int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int nMapWidth,
		const int nMapHeight, int* pOutBuffer, const int nOutBufferSize)
{
	std::map<int, Node> nodeMap;
	PriorityQueue<Node*, int> openNodesQueue;

	//********************************************************************************************************************************
	// create start node
	int startIndex = ComputeIndex(nStartX, nStartY, nMapWidth);

	nodeMap.emplace(startIndex, Node(startIndex, 0));
	openNodesQueue.Push(&nodeMap.at(startIndex), 0);

	//
	int targetIndex = ComputeIndex(nTargetX, nTargetY, nMapWidth);
	int mapSize = nMapWidth * nMapHeight;

	//********************************************************************************************************************************
	// search the map (A*)
	Node* targetNode = NULL;

	while (!openNodesQueue.Empty())
	{
		Node* currentNode;
		int priority = openNodesQueue.Pop(currentNode);

		//if the node has been updated since it was inserted, ignore
		if (priority != currentNode->GetTotalCost())
		{
			continue;
		}

		int currentNodeIndex = currentNode->GetIndex();

		//***********************************
		//check if we reached the destination
		if (currentNodeIndex == targetIndex)
		{
			targetNode = currentNode;
			break;
		}

		//***********************************
		//compute neighbouring positions
		std::vector<int> neighbourPositions;
		int neighbourCount = 0;
		int previousNodeIndex = currentNode->GetPreviousNodeIndex();

		if (currentNodeIndex + 1 < mapSize && (currentNodeIndex + 1) % nMapWidth != 0 && previousNodeIndex != currentNodeIndex + 1)
		{
			neighbourPositions.push_back(currentNodeIndex + 1);
			neighbourCount++;
		}

		if (currentNodeIndex - 1 >= 0 && currentNodeIndex % nMapWidth != 0 && previousNodeIndex != currentNodeIndex - 1)
		{
			neighbourPositions.push_back(currentNodeIndex - 1);
			neighbourCount++;
		}

		if (currentNodeIndex + nMapWidth < mapSize && previousNodeIndex != currentNodeIndex + nMapWidth)
		{
			neighbourPositions.push_back(currentNodeIndex + nMapWidth);
			neighbourCount++;
		}

		if (currentNodeIndex - nMapWidth >= 0 && previousNodeIndex != currentNodeIndex - nMapWidth)
		{
			neighbourPositions.push_back(currentNodeIndex - nMapWidth);
			neighbourCount++;
		}

		//***********************************
		//visit current node
		for (int i = 0; i < neighbourCount; i++)
		{
			int neighbourIndex = neighbourPositions[i];

			//if the neighbour tile is impassable we can continue
			if (pMap[neighbourIndex] == 0)
			{
				continue;
			}

			std::map<int, Node>::iterator nodeIterator = nodeMap.find(neighbourIndex);

			if (nodeIterator != nodeMap.end())
			{
				Node* neighbourNode = &nodeIterator->second;
				int movementCost = currentNode->GetMovementCost() + 1;

				if (neighbourNode->GetMovementCost() > movementCost)
				{
					neighbourNode->SetPreviousNode(currentNodeIndex, movementCost);
					openNodesQueue.Push(neighbourNode, movementCost + neighbourNode->GetRemainingCost());
				}
			}
			else
			{
				int remainingCost = ComputeRemainingCost(neighbourIndex, targetIndex, nMapWidth);

				nodeMap.emplace(neighbourIndex, Node(neighbourIndex, remainingCost));

				Node* neighbourNode = &nodeMap.at(neighbourIndex);

				neighbourNode->SetPreviousNode(currentNodeIndex, currentNode->GetMovementCost() + 1);
				openNodesQueue.Push(neighbourNode, neighbourNode->GetTotalCost());
			}
		}
	}

	//********************************************************************************************************************************
	// build the path

	int pathLength = -1;

	if (targetNode != NULL)
	{
		std::vector<int> path;
		int currentIndex = targetIndex;
		Node* currentNode = NULL;
		pathLength = 0;

		while (currentIndex != startIndex)
		{
			path.push_back(currentIndex);
			currentNode = &nodeMap.at(currentIndex);
			currentIndex = currentNode->GetPreviousNodeIndex();
			pathLength++;
		}

		std::reverse(path.begin(), path.end());

		int croppedPathLength = std::min(pathLength, nOutBufferSize);

		for (int i = 0; i < croppedPathLength; i++)
		{
			pOutBuffer[i] = path.at(i);
		}
	}

	return pathLength;
}

