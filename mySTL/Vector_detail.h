#pragma once
#ifndef _VECTOR_DETAIL_H
#define _VECTOR_DETAIL_H
namespace STL {
	//*********************************构造、析构**************************************

	template<class T, class Alloc>
	vector<T, Alloc>::~vector() {
		deallocate();
	}

	template<class T, class Alloc>
	vector<T, Alloc>::vector(const size_type n) {
		allocate_and_fill_n(n, value_type());
	}
	template<class T, class Alloc>
	vector<T, Alloc>::vector(size_type n, const value_type& value) {
		allocate_and_fill_n(n, value);
	}

	//********************************空间配置器相关*********************
	template<class T, class Alloc>
	template<class InputIterator>
	void vector<T, Alloc>::__insert(iterator position
		, InputIterator first
		, InputIterator last
		, std::false_type) {
		difference_type leftSize = end_of_storage - finish_;  //容器中剩余空间
		difference_type needSize = distance(first, last);// last --> first
		if (leftSize >= needSize) {
			if (finish_ - position > needSize) {
				
			}
		}
	}
	
	template<class T, class Alloc>
	template<class Integer>
	void vector<T, Alloc>::__insert(iterator position
		, Integer n
		, const value_type& value
		, std::true_type) {

	}

	template<class T, class Alloc>
	void vector<T, Alloc>::fill_initialize(size_t n, const value_type& value) {
		allocate_and_fill_n(n, value);
		finish_ = start_ + n;
		end_of_storage = finish_;
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::allocate_and_fill_n(size_type n, const T& value) {
		start_ = data_Allocater::allocate(n);//配置n个元素的空间
		STL::uninitialized_fill_n(start_, start_ + n, value);
		finish_ = end_of_storage = start_ + n;
	}
	template<class T, class Alloc>
	void vector<T, Alloc>::deallocate() {
		if (start_) {//存在被配置过的空间
			data_Allocator::destory(start_,finish_);
			data_Allocator::deallocate(start_, capacity());
		}
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::reallocate(size_t n = 0) {

	}

	template<class T, class Alloc>
	void vector<T, Alloc>::clear() {
		data_Allocator::destory(start_, finish_);
		finish_ = start_;
	}
	template<class T, class Alloc>
	void vector<T, Alloc>::pop_back() {
		--finish_;
		data_Allocator::destroy(finish_);
	}

	//*********************************容器比较函数*****************************

	template<class T, class Alloc>
	bool vector<T, Alloc>::operator ==(const vector& rhs) {
		if (rhs.size() != this->size()) {
			return false;
		}
		auto ptrLhs = this->start_;
		auto ptrRhs = rhs.start_;
		for (; ptrLhs != this->finish_ && ptrRhs != rhs.finish_; ++ptrLhs, ++ptrRhs) {
			if (*ptrLhs != *ptrRhs)
				return false;
		}
		return true;
	}
	template<class T, class Alloc>
	bool vector<T, Alloc>::operator !=(const vector& v) {
		return !(*this == v);
	}

	template<class T, class Alloc>
	bool operator == (const vector<T, Alloc>& v1, const vector<T, Alloc>& v2) {

		return v1.operator==(v2);
	}
	template<class T, class Alloc>
	bool operator != (const vector<T, Alloc>& v1, const vector<T, Alloc>& v2) {

		return !(v1 == v2);
	}

	//*******************************对容器进行修改的内部函数******************

	template<class T, class Alloc>
	void  vector<T, Alloc>::push_back(const value_type & value) {
		insert(end(), value);
	}
	template<class T, class Alloc>
	void vector<T, Alloc>::insert(iterator position
		, const size_type& n
		, const value_type& value) {
		__insert(position, n, value, typename std::_Is_integral<size_type>::type());
	}
	template<class T, class Alloc>
	template <class InputIterator>
	void vector<T, Alloc>::insert(iterator position
		, InputIterator first
		, InputIterator last) {
		__insert(position, first, last, typename std::_Is_integral<InputIterator>::type());
	}

	//*******************************容器容量相关的操作函数********************
}
#endif