#ifndef PRIORITY_QUEUE_HPP_
#define PRIORITY8QUEUE_HPP_

#include <queue>
#include <utility>

template <typename T, typename priority_t>
class PRIORITY_QUEUE
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
	PRIORITY_QUEUE()
	{
	}

	virtual ~PRIORITY_QUEUE()
	{
	}

	//################################################

	// -- INQUIRIES


	bool IsEmpty() const
	{
		return ElementsQueue.empty();
	}

	//################################################

	// -- OPERATIONS

  public:
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

#endif /* PRIORITY_QUEUE_HPP_ */
