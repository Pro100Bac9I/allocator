#include <iostream>
#include <map>

#include "allocator.h"
#include "mylist.h"

int factorial(int n)
{
	int value = 1;
	for(int i = 2; i <= n; ++i)
		value *= i;
	return value;
}

int main()
{
	
	{
		std::map<int, int> mp;
		for (int i = 1; i < 10; ++i)
			mp[i] = factorial(i);

		for(const auto &p : mp)
			std::cout << p.first << ' ' << p.second << std::endl; 
	}

	{
		std::map<int, int, std::less<int>, MyAllocator<std::pair<int, int>>> mp;
		for (int i = 1; i < 10; ++i)
			mp[i] = factorial(i);

		for(const auto &p : mp)
			std::cout << p.first << ' ' << p.second << std::endl; 
	}
	
	{
		MyList<int> lst;
		for (int i = 0; i < 10; ++i)
			lst.push_back(i);

		for(auto it = lst.begin(); it != nullptr; it = it->next)
		{
			std::cout << it->value << ' ';
		}
		std::cout << std::endl;
	}

	
	{
		MyList<int, MyAllocator<ListNode<int>>> lst;
		for (int i = 0; i < 10; ++i)
			lst.push_back(i);

		for(auto it = lst.begin(); it != nullptr; it = it->next)
		{
			std::cout << it->value << ' ';
		}
		std::cout << std::endl;
	
	}
	
	return 0;
}