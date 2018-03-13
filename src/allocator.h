#pragma once
#include <cstdlib>

#define SIZE 10

template <class T>
class MyAllocator
{
public:
	using value_type = T;

	using const_pointer = const T*;
	using pointer = T * ;
	using const_reference = const T&;
	using reference = T & ;

	template <typename U>
	struct rebind
	{
		using other = MyAllocator<U>;
	};

	explicit MyAllocator(size_t size_ = SIZE) :
			size(size_)
	{
		headPointer = reinterpret_cast<pointer>(malloc(size * sizeof(T)));
		currentPosition = headPointer;
	}

	MyAllocator(const MyAllocator& other) :
		size(other.size),
		headPointer(other.headPointer),
		currentPosition(other.currentPosition)
	{
	}

	template <class U>
	MyAllocator(const MyAllocator<U> &) :
		size(0),
		headPointer(nullptr),
		currentPosition(nullptr)
	{
	}

	void operator=(MyAllocator &&) = delete;
	void operator=(const MyAllocator &) = delete;

	~MyAllocator()
	{

		//std::cout << "dtor" << std::endl;
		if (headPointer)
			free(headPointer);
	}

	template<typename U, typename... Args>
	void construct(U *p, Args&&... args)
	{
		//std::cout << "construct" << std::endl;
		new((void *)p) U(std::forward<Args>(args)...);
	}

	void destroy(pointer p)
	{
		//std::cout << "destroy" << std::endl;
		p->~T();
	}

	T* allocate(size_t n)
	{
		//std::cout << "alloc" << std::endl;
		pointer ptr = currentPosition;
		currentPosition += n;
		return ptr;
	}

	void deallocate(pointer ptr, size_t)
	{
		//std::cout << "dealloc" << std::endl;
	}

private:
	size_t size;
	pointer headPointer;
	pointer currentPosition;
};

template<typename T>
inline bool operator ==(const MyAllocator<T> &left, const MyAllocator<T> &right) {
		return false;
}

template<typename T>
inline bool operator !=(const MyAllocator<T> &left, const MyAllocator<T> &right) {
		return true;
}

