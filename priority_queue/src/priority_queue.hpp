#ifndef SJTU_PRIORITY_QUEUE_HPP
#define SJTU_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <functional>
#include "exceptions.hpp"

namespace sjtu {

/**
 * a container like std::priority_queue which is a heap internal.
 */
template<typename T, class Compare = std::less<T>>
class priority_queue {
public:
	/**
	 * TODO constructors
	 */
	priority_queue() {}
	priority_queue(const priority_queue &other) {}
	/**
	 * TODO deconstructor
	 */
	~priority_queue() {}
	/**
	 * TODO Assignment operator
	 */
	priority_queue &operator=(const priority_queue &other) {}
	/**
	 * get the top of the queue.
	 * @return a reference of the top element.
	 * throw container_is_empty if empty() returns true;
	 */
	const T & top() const {

	}
	/**
	 * TODO
	 * push new element to the priority queue.
	 */
	void push(const T &e) {

	}
	/**
	 * TODO
	 * delete the top element.
	 * throw container_is_empty if empty() returns true;
	 */
	void pop() {

	}
	/**
	 * return the number of the elements.
	 */
	size_t size() const {

	}
	/**
	 * check if the container has at least an element.
	 * @return true if it is empty, false if it has at least an element.
	 */
	bool empty() const {

	}
	/**
	 * merge two priority_queues with at most O(logn) complexity.
	 * clear the other priority_queue.
	 */
	void merge(priority_queue &other) {

	}
};

}

#endif
