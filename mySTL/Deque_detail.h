#include"Deque.h"
#ifndef _DEQUE_DETAIL_H_
#define _DEQUE_DETAIL_H_
namespace STL {
	namespace Detail {

		template<class T>
		deque_iterator<T> & deque_iterator<T>::operator = (const deque_iterator & it)
		{
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
			else if (mapIndex_ + 1 < container_->map_size_) {//已经在桶的结尾，但是之后还有新的map指针
				++mapIndex_;
				cur_ = getBuckHead(mapIndex_);
			}
			else {//+1之后没有了map
				mapIndex = container_->map_size_;
			//	cur_ = container_->map_[mapIndex_];//指向结尾的
			}
		}
		template<class T>
		deque_iterator<T> deque_iterator<T>::operator++(int)
		{
			return deque_iterator();
		}
		template<class T>
		deque_iterator<T>  & deque_iterator<T>::operator--()
		{
			// TODO: 在此处插入 return 语句
		}
		template<class T>
		deque_iterator<T> deque_iterator<T>::operator--(int)
		{
			return deque_iterator();
		}
		template<class T>
		bool deque_iterator<T>::operator==(const dq_iter & rhs) const
		{
			return ((mapIndex_ == rhs.mapIndex_)
				&& (cur_ == rhs.cur_)
				&& (container_ == rhs.container_));
		}
		template<class T>
		inline bool deque_iterator<T>::operator!=(const dq_iter & rhs) const
		{
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
			return container_->map_[mapIndex_]);
		}
		template<class T>
		inline size_t deque_iterator<T>::getBuckSize()
		{
			return container_->getBuckSize();
		}
		template<class T>
		bool operator==(const deque_iterator<T>& lhs, const deque_iterator<T>& rhs)
		{
			return
		}
		template<class T>
		bool operator!=(const deque_iterator<T>& lhs, const deque_iterator<T>& rhs)
		{
			return false;
		}

	}//end of Detail

	template<class T, class Alloc>
	T * deque<T, Alloc>::getANewBuck()
	{

	}
	template<class T, class Alloc>
	T ** deque<T, Alloc>::getANewMap(const size_t size)
	{

	}
	template<class T, class Alloc>
	size_t deque<T, Alloc>::getNewMapSize(const size_t size)
	{

	}
}


#endif // !_DEQUE_DETAIL_H_
