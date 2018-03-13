#pragma once
#include <iostream>

template<class T>
struct ListNode
{
		ListNode(const T val = 0): value(val), next(nullptr) {};
		T value;
		ListNode * next;

};

template<class T, class Allocator = std::allocator<ListNode<T>>>
class MyList
{
public:
		using NodeType = ListNode<T>;
		using iterator = NodeType*;

public:
	MyList() : 
	  length(0), 
	  head(nullptr), 
	  tail(nullptr) 
	 {}

	~MyList()
	{
		iterator curPtr = head;
		while(curPtr)
		{
			iterator ptrToDelete = curPtr;
			curPtr = curPtr->next;
			allocator.destroy(ptrToDelete);
			allocator.deallocate(ptrToDelete, 1);

		}
		 
	}
	
	size_t size() const 
	{ 
		return length; 
	}
	bool empty() const 
	{ 
		return head == nullptr; 
	}
	
	void push_back(const T &value)
	{
		auto ptr = allocator.allocate(1);
		if (!ptr)
			return;

		allocator.construct(ptr, value);

		if (length)
		{
			tail->next = ptr;
			tail = ptr;

		}
		else
		{
			head = tail = ptr;
		}
		length++;
	}

	iterator begin() 
	{ 
		return head;
	}
	iterator end()
	{
		return tail;
	}

private:
	size_t length;
	NodeType *head;
	NodeType *tail;
	Allocator allocator;
	
};




