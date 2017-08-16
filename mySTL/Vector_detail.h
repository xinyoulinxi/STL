#pragma once
#ifndef _VECTOR_DETAIL_H
#define _VECTOR_DETAIL_H
namespace STL {
	//*********************************构造、析构**************************************

	template<class T, class Alloc>
	vector<T, Alloc>::vector(const size_type n) {
		
	}


	template<class T, class Alloc>
	vector<T, Alloc>::vector(size_type n, const value_type& value) {

	}
	//空间配置器相关
	template<class T, class Alloc>
	void vector<T, Alloc>::fill_initialize(size_t n, const value_type& value) {
		allocate_and_fill(n, value);
		end_ = begin_ + n;
		end_of_storage = end_;
	}

	template<class T, class Alloc>
	iterator vector<T, Alloc>::allocate_and_fill(size_type n, const T& x) {

	}
	template<class T, class Alloc>
	void vector<T, Alloc>::deallocate() {
		if (begin_) {
			
		}
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::reallocate(size_t n = 0) {

	}
	
}
#endif