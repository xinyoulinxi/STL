#ifndef _CONSTRUCT_H_
#define _CONSTRUCT_H_

#include"type_traits.h"
#include<new>
namespace STL {
	template<typename T1, typename T2>
	inline void construct(T1* p, const T2& value) {
		new(p)T1(value);
	}
	//调用析构函数,第一个版本，接受一个指针

	template<typename T>
	inline void destory(T* pointer) {
		pointer->~T();
	}
	//接收两个迭代器
	template<class ForwordIterator>
	inline void destory(ForwordIterator first, ForwordIterator last) {
		__destory(first, last);
	}

	template<class ForwardIterator>
	inline void __destory(ForwardIterator first, ForwardIterator last) {
		typedef typename STL::__type_traits<ForwardIterator>::has_trivial_destructor trivial_destoructor;
		__destory_aux(first, last, trivial_destoructor);
	}

	template<class ForwardIterator>
	inline void __destroy(ForwardIterator first, ForwardIterator last, __true_type) {}

	template<class ForwardIterator>
	void __destory_aux(ForwardIterator first, ForwardIterator last, STL::__false_type) {
		for (; first < last; ++first) {
			destory(&*first);
		}
	}
}
#endif