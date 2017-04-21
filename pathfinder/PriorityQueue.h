/*
 * PriorityQueue.h
 *
 *  Created on: Mar 19, 2017
 *      Author: patrick
 */

#ifndef PATHFINDER_PRIORITYQUEUE_H_
#define PATHFINDER_PRIORITYQUEUE_H_

#include <queue>

using namespace std;

template<typename T, typename priority_t>
class PriorityQueue
{
	typedef pair<priority_t, T> element;

	struct PriorityCompare
	{
		bool operator()(const element& lhs, const element& rhs)
		{
			return lhs.first > rhs.first;
		}
	};

public:
	inline bool Empty() const
	{
		return elements.empty();
	}

	inline void Push(T item, priority_t priority)
	{
		elements.emplace(priority, item);
	}

	inline priority_t Pop(T& item)
	{
		/*T item = elements.top().second;
		elements.pop();
		return item;*/
		element e = elements.top();
		priority_t p = e.first;
		item = e.second;
		elements.pop();
		return p;
	}

private:
	priority_queue<element, vector<element>, PriorityCompare> elements;
};

#endif /* PATHFINDER_PRIORITYQUEUE_H_ */
