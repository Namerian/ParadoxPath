/*
 * PriorityQueue.h
 *
 *  Created on: Mar 19, 2017
 *      Author: patrick
 */

#ifndef PATHFINDER_PRIORITYQUEUE_H_
#define PATHFINDER_PRIORITYQUEUE_H_

#include <queue>
#include <utility>

template <typename T, typename priority_t>
class PriorityQueue
{
	//################################################

	typedef std::pair<priority_t, T> ELEMENT;

	struct PRIORITY_COMPARE
	{
		bool operator()(const ELEMENT &lhs, const ELEMENT &rhs)
		{
			return lhs.first > rhs.first;
		}
	};

	//################################################

	// -- ATTRIBUTES

  private:
	std::priority_queue<ELEMENT, std::vector<ELEMENT>, PRIORITY_COMPARE> ElementsQueue;

	// ################################################

	// -- INITIALIZATION

  public:
	PriorityQueue()
	{
	}

	virtual ~PriorityQueue()
	{
	}

	//################################################

	// -- OPERATIONS

  public:
	bool Empty() const
	{
		return ElementsQueue.empty();
	}

	void Push(T item, priority_t priority)
	{
		ElementsQueue.emplace(priority, item);
	}

	priority_t Pop(T &item)
	{
		ELEMENT element = ElementsQueue.top();
		priority_t priority = element.first;
		item = element.second;
		ElementsQueue.pop();
		return priority;
	}
};

#endif /* PATHFINDER_PRIORITYQUEUE_H_ */
