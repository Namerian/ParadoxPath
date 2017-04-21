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
public:
	Node()
	{
	}

	Node(const int index, const int remainingCost){
		_nodeIndex = index;
		_remainingCost=remainingCost;
	}

	Node(const Node& node){
		_nodeIndex=node._nodeIndex;
		_remainingCost = node._remainingCost;
	}

	virtual ~Node()
	{
	}

	inline void SetPreviousNode(int previousNodeIndex, int newMovementCost)
	{
		_previousNodeIndex = previousNodeIndex;
		_movementCost = newMovementCost;
	}

	inline int GetRemainingCost() const
	{
		return _remainingCost;
	}

	inline int GetMovementCost() const
	{
		return _movementCost;
	}

	inline int GetTotalCost() const
		{
			return _movementCost + _remainingCost;
		}

	inline int GetPreviousNodeIndex() const
	{
		return _previousNodeIndex;
	}

	inline int GetIndex() const{
		return _nodeIndex;
	}

private:
	int _remainingCost = 0;
	int _movementCost = 0;

	int _previousNodeIndex = 0;
	int _nodeIndex = -1;
};

#endif /* PATHFINDER_NODE_H_ */
