#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include<new>
#include"alloc.h"
#include"Construct.h"
namespace STL{

	/*
    **对alloc出来的地址空间进行placement new 构造
	**以及对自身构造出来的内容进行对应的析构
	*/
	template <class T>
	class allocator{
	public:
		typedef T			value_type;
		typedef T*			pointer;
		typedef const T*	const_pointer;
		typedef T&			reference;
		typedef const T&	const_reference;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;

	public:
		//分配未构造的内存空间，使用自带的alloc
		static T *allocate();
		static T *allocate(size_t n);
		static void deallocate(T *ptr);
		static void deallocate(T *ptr, size_t n);


		/*
		**以下的构造和析构都是针对带有构造函数和析构函数的对象
		**对于基本对象直接返回内存空间
		*/
		static void construct(T *ptr);
		static void construct(T *ptr, const T& value);
		static void destroy(T *ptr);
		static void destroy(T *first, T *last);

	public:
		allocator() {};
		~allocator() {};
	};
	
	template<class T>
	T *allocator<T>::allocate() {
		return static_cast<T *>(alloc::allocate(sizeof(T)));
	}
	template<class T>
	T *allocator<T>::allocate(size_t n) {
		if (n == 0) return 0;
		return static_cast<T *>(alloc::allocate(sizeof(T) * n));
	}
	template<class T>
	void allocator<T>::deallocate(T *ptr) {
		alloc::deallocate(static_cast<void *>(ptr), sizeof(T));
	}
	template<class T>
	void allocator<T>::deallocate(T *ptr, size_t n) {
		if (n == 0) return;
		alloc::deallocate(static_cast<void *>(ptr), sizeof(T)* n);
	}

	template<class T>
	void allocator<T>::construct(T *ptr) {//调用default placement new 
		new(ptr)T();
	}
	template<class T>
	void allocator<T>::construct(T *ptr, const T& value) {//带参调用 placement new 
		new(ptr)T(value);
	}
	template<class T>
	void allocator<T>::destroy(T *ptr) {// 调用 operator delete 去析构 T
		ptr->~T();
	}
	template<class T>
	void allocator<T>::destroy(T *first, T *last) {
		for (; first != last; ++first) {
			first->~T();
		}
	}

}
#endif