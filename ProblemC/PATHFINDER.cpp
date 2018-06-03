#include <cstddef>
#include <map>
#include <cmath>
#include <algorithm>
#include <vector>

#include <iostream>

#include "PATHFINDER.hpp"
#include "NODE.hpp"
#include "PRIORITY_QUEUE.hpp"

/**
 * Computes the index of a node from its position.
 */
int ComputeIndex(const int position_x, const int position_y, const int map_width)
{
	return position_x + position_y * map_width;
}

/**
 * Estimates the distance between 2 nodes.
 */
double ComputeRemainingCost(const int current_node_index, const int map_width, //
							const int start_x, const int start_y,			   //
							const int target_x, const int target_y)			   //
{
	int current_x = current_node_index % map_width;
	int current_y = current_node_index / map_width;

	int distance_x = std::abs(target_x - current_x);
	int distance_y = std::abs(target_y - current_y);

	/**
	 * The following is for tie-breaking.
	 */
	int dx1 = current_x - target_x;
	int dy1 = current_y - target_y;
	int dx2 = start_x - target_x;
	int dy2 = start_y - target_y;
	double cross = std::abs(dx1 * dy2 - dx2 * dy1);

	return (distance_x + distance_y) + (cross * 0.0001);
}

//==================================================================================
//
//==================================================================================

int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char *pMap, const int nMapWidth, const int nMapHeight, int *pOutBuffer, const int nOutBufferSize)
{
	std::map<int, NODE> node_map;
	PRIORITY_QUEUE<NODE *, double> open_nodes_queue;

	int start_index = ComputeIndex(nStartX, nStartY, nMapWidth);

	node_map.emplace(start_index, NODE(start_index, 0));
	open_nodes_queue.Push(&node_map.at(start_index), 0);

	int target_index = ComputeIndex(nTargetX, nTargetY, nMapWidth);
	int map_size = nMapWidth * nMapHeight;

	NODE *target_node = NULL;

	while (!open_nodes_queue.IsEmpty())
	{
		NODE *current_node;
		double current_node_priority = open_nodes_queue.Pop(current_node);

		/**
		 * If the node has been updated since it was inserted, ignore it.
		 * Because that means it has been reintroduced into the queue with a new priority.
		 */
		if (current_node_priority != current_node->GetTotalCost())
		{
			continue;
		}

		int current_node_index = current_node->GetIndex();

		/**
		 * If the current node is the target, the search is interrupted!
		 */
		if (current_node_index == target_index)
		{
			target_node = current_node;
			break;
		}

		/**
		 * A vector with all the traversable neighbours of the current node that need to be checked.
		 */
		std::vector<int> neighbouring_positions_vector;
		int previous_node_index = current_node->GetPreviousNodeIndex();

		int right_neighbour_index = current_node_index + 1;
		int left_neighbour_index = current_node_index - 1;
		int down_neighbour_index = current_node_index + nMapWidth;
		int up_neighbour_index = current_node_index - nMapWidth;

		if (right_neighbour_index < map_size				// boundary check
			&& right_neighbour_index % nMapWidth != 0		// boundary check - is current node on the right edge of the row?
			&& right_neighbour_index != previous_node_index // already checked
			&& pMap[right_neighbour_index] == 1)			// is traversable?
		{
			neighbouring_positions_vector.push_back(right_neighbour_index);
		}

		if (left_neighbour_index >= 0					   // boundary check
			&& current_node_index % nMapWidth != 0		   // boundary check - is current node on the left edge of the row?
			&& left_neighbour_index != previous_node_index // already checked
			&& pMap[left_neighbour_index] == 1)			   // is traversable?
		{
			neighbouring_positions_vector.push_back(left_neighbour_index);
		}

		if (down_neighbour_index < map_size				   // boundary check - is current node in the last row?
			&& down_neighbour_index != previous_node_index // already checked
			&& pMap[down_neighbour_index] == 1)			   // is traversable?
		{
			neighbouring_positions_vector.push_back(down_neighbour_index);
		}

		if (up_neighbour_index >= 0						 // boundary check - is current node in the first row?
			&& up_neighbour_index != previous_node_index // already checked
			&& pMap[up_neighbour_index] == 1)			 // is traversable?
		{
			neighbouring_positions_vector.push_back(up_neighbour_index);
		}

		/**
		 * Visiting the neighbours
		 */
		for (int i = 0; i < neighbouring_positions_vector.size(); i++)
		{
			int neighbour_index = neighbouring_positions_vector[i];
			std::map<int, NODE>::iterator iterator_to_neighbour = node_map.find(neighbour_index);

			if (iterator_to_neighbour != node_map.end())
			{
				NODE *neighbour_node = &iterator_to_neighbour->second;
				int new_movement_cost = current_node->GetMovementCost() + 1;
				double new_total_cost = new_movement_cost + neighbour_node->GetRemainingCost();

				if (new_total_cost < neighbour_node->GetTotalCost())
				{
					neighbour_node->SetPreviousNode(current_node_index, new_movement_cost);
					open_nodes_queue.Push(neighbour_node, neighbour_node->GetTotalCost());
				}
			}
			else
			{
				double remaining_cost = ComputeRemainingCost(neighbour_index, nMapWidth, nStartX, nStartY, nTargetX, nTargetY);
				node_map.emplace(neighbour_index, NODE(neighbour_index, remaining_cost));
				NODE *neighbour_node = &node_map.at(neighbour_index);

				neighbour_node->SetPreviousNode(current_node_index, current_node->GetMovementCost() + 1);
				open_nodes_queue.Push(neighbour_node, neighbour_node->GetTotalCost());
			}
		}
	}

	/**
	 * Building the path
	 */

	int pathLength = -1;

	if (target_node != NULL) // The path can only be build if the target has been reached.
	{
		std::vector<int> path;
		int currentIndex = target_index;
		NODE *currentNode = NULL;
		pathLength = 0;

		while (currentIndex != start_index)
		{
			path.push_back(currentIndex);
			currentNode = &node_map.at(currentIndex);
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
