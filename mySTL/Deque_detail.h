#include"Deque.h"
#ifndef _DEQUE_DETAIL_H_
#define _DEQUE_DETAIL_H_
namespace STL {
	namespace Detail {

		template<class T>
		deque_iterator<T> & deque_iterator<T>::operator = (const deque_iterator & it) {
			if (this != &it) {
				this->cur_ = it.cur_;
				this->mapIndex_ = it.mapIndex_;
				this->container_ = it.container_;
			}
			return *this;
		}

		template<class T>
		deque_iterator<T>  & deque_iterator<T>::operator++() {
			if (cur_ != getNowBuckTail()) {//+1之后依然在桶内
				++cur;
			}
			else if (mapIndex_ + 1 < container_->mapSize_) {//已经在桶的结尾，但是之后还有新的map指针
				++mapIndex_;
				cur_ = getNowBuckHead();//指向下一个桶的开头
			}
			else {//mapIndex_ +1之后没有了map
				mapIndex_ = container_->mapSize_;

				cur_ = container_->map_[mapIndex_];//指向未知区域
			}
			return *this;
		}
		template<class T>
		deque_iterator<T> deque_iterator<T>::operator++(int) {
			auto tmp = *this;
			++*this;
			return tmp;
		}
		template<class T>
		deque_iterator<T>  & deque_iterator<T>::operator--() {
			if (cur_ != getNowBuckHead()) {
				--cur_;
			}
			else if (mapIndex_ - 1 >= 0) {
				--mapIndex_;
				cur_ = getNowBuckHead();
			}
			else {
				mapIndex = 0;
				cur_ = container_->map_[mapIndex_];
			}

		}
		template<class T>
		deque_iterator<T> deque_iterator<T>::operator--(int)
		{
			auto retIter = *this;
			--*this;
			return retIter;
		}
		template<class T>
		bool deque_iterator<T>::operator==(const deque_iterator & rhs) const {
			return ((mapIndex_ == rhs.mapIndex_)
				&& (cur_ == rhs.cur_)
				&& (container_ == rhs.container_));
		}
		template<class T>
		inline bool deque_iterator<T>::operator!=(const deque_iterator & rhs) const {
			return !(rhs == *this);
		}
		template<class T>
		deque_iterator<T> deque_iterator<T>::getNowBuckTail()
		{
			return container_->map_[mapIndex_] + (container_->getBuckSize() - 1);
		}
		template<class T>
		deque_iterator<T> deque_iterator<T>::getNowBuckHead()
		{
			return container_->map_[mapIndex_];
		}
		template<class T>
		inline size_t deque_iterator<T>::getBuckSize() {
			return container_->getBuckSize();
		}

	}//end of Detail

	template<class T, class Alloc>
	T * deque<T, Alloc>::getANewBuck(){
		return dataAllocator::allocate(getBuckSize());//未构造空间
	}
	template<class T, class Alloc>
	T ** deque<T, Alloc>::getANewMap(const size_t size){
		T **map = new T*[size];
		for (int i = 0; i != size; ++i) {
			map[i] = getANewBuck();
		}
		return map;
	}
	template<class T, class Alloc>
	size_t deque<T, Alloc>::getNewMapSize(const size_t size){
		return (size == 0 ? 2 : size + 2);
	}
	//元素访问
	template<class T, class Alloc>
	deque<T, Alloc>::reference deque<T, Alloc>::operator[] (size_type n) {
		return *(begin() + n);
	}
	template<class T, class Alloc>
	deque<T, Alloc>::reference deque<T, Alloc>::front() {
		return *begin();
	}
	template<class T, class Alloc>
	deque<T, Alloc>::reference deque<T, Alloc>::back() {
		return *(end() - 1);
	}
	//构造函数相关
	template<class T, class Alloc>
	deque<T, Alloc>::deque() {
		
		
	}
		
	template<class T, class Alloc>
	deque<T, Alloc>::deque(size_t n, const value_type & value = value_type()) {

	}
	template<class T, class Alloc>
	
	template <class InputIterator>
	deque<T, Alloc>::deque(InputIterator first, InputIterator last) {

	}
	template<class T, class Alloc>
	deque<T, Alloc>::deque(const deque& rhs) {

	}
	template<class T, class Alloc>
	deque<T, Alloc>::~deque() {

	}

	//元素操作相关
	template<class T, class Alloc>
	void deque<T, Alloc>::push_back() {

	}
	template<class T, class Alloc>
	void deque<T, Alloc>::deque<T, Alloc>::pop_back() {

	}
	template<class T, class Alloc>
	void deque<T, Alloc>::push_front() {

	}
	template<class T, class Alloc>
	void deque<T, Alloc>::pop_front() {

	}
	template<class T, class Alloc>
	void deque<T, Alloc>::clear() {

	}
	template<class T, class Alloc>
	void deque<T, Alloc>::init() {
		mapSize_ = 2;
		map_ = getANewMap();
		//将起始点放置在中间
		start_.container_ = finish_.container_ = this;
		start_.mapIndex_ = finish_.mapIndex_ = mapSize_ - 1;
		start_.cur_ = finish_.cur_ = map_[mapSize_ - 1];
	}
}


#endif // !_DEQUE_DETAIL_H_
