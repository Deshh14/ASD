#include <iostream>

template <class T>
class Queue
{
	T* data;
	int _head;
	int _capacity;
	int _count;
	int _size;
public:
	Queue(int size);
	~Queue();
	Queue(const Queue& other);

	Queue& operator=(const Queue& other);
	void push(const T& val);
	void pop();
	inline T top() const;
	inline bool is_empty() const noexcept;
	inline bool is_full() const noexcept;
	void clear() noexcept;
	int count() const;
	int head() const;
	int size() const;
};
