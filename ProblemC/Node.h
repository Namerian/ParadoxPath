/*
 * Node.h
 *
 *  Created on: Mar 19, 2017
 *      Author: patrick
 */

#ifndef PATHFINDER_NODE_H_
#define PATHFINDER_NODE_H_

class Node
{
	//################################################

	// -- ATTRIBUTES

  private:
	int RemainingCost = 0;
	int MovementCost = 0;

	int PreviousNodeIndex = 0;
	int NodeIndex = -1;

	//################################################

	// -- INITIALIZATION

  public:
	Node()
	{
	}

	Node(const int index, const int remaining_cost)
	{
		NodeIndex = index;
		RemainingCost = remaining_cost;
	}

	Node(const Node &node)
	{
		NodeIndex = node.NodeIndex;
		RemainingCost = node.RemainingCost;
	}

	virtual ~Node()
	{
	}

	//################################################

	// -- INQUIRIES

  public:
	int GetRemainingCost() const
	{
		return RemainingCost;
	}

	int GetMovementCost() const
	{
		return MovementCost;
	}

	int GetTotalCost() const
	{
		return MovementCost + RemainingCost;
	}

	int GetPreviousNodeIndex() const
	{
		return PreviousNodeIndex;
	}

	int GetIndex() const
	{
		return NodeIndex;
	}

	//################################################

	// -- OPERATIONS

  public:
	void SetPreviousNode(int previousNodeIndex, int newMovementCost)
	{
		PreviousNodeIndex = previousNodeIndex;
		MovementCost = newMovementCost;
	}
};

#endif /* PATHFINDER_NODE_H_ */
