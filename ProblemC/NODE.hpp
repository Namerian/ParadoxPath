#ifndef NODE_HPP_
#define NODE_HPP_

class NODE
{
	//################################################

	// -- ATTRIBUTES

  private:
	double RemainingCost = 0;
	int MovementCost = 0;

	int PreviousNodeIndex = 0;
	int NodeIndex = -1;

	//################################################

	// -- INITIALIZATION

  public:
	NODE()
	{
	}

	NODE(const int index, const double remaining_cost)
	{
		NodeIndex = index;
		RemainingCost = remaining_cost;
	}

	NODE(const NODE &node)
	{
		NodeIndex = node.NodeIndex;
		RemainingCost = node.RemainingCost;
	}

	virtual ~NODE()
	{
	}

	//################################################

	// -- INQUIRIES

  public:
	double GetRemainingCost() const
	{
		return RemainingCost;
	}

	int GetMovementCost() const
	{
		return MovementCost;
	}

	double GetTotalCost() const
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
	void SetPreviousNode(int previous_node_index, int new_movement_cost)
	{
		PreviousNodeIndex = previous_node_index;
		MovementCost = new_movement_cost;
	}
};

#endif /* NODE_HPP_ */
