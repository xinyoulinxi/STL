#include"Deque.h"
#ifndef _DEQUE_DETAIL_H_
#define _DEQUE_DETAIL_H_
namespace STL {
	namespace Detail {

		template<class T>
		deque_iterator<T> & deque_iterator<T>::operator = (const deque_iterator & it){
			if (this != &it) {
				this->cur_ = it.cur_;
				this->mapIndex_ = it.mapIndex_;
				this->container_ = it.container_;
			}
			return *this;
		}
		
		template<class T>
		deque_iterator<T>  & deque_iterator<T>::operator++() {
			if (cur_ != getNowBuckTail(mapIndex_)) {//+1之后依然在桶内
				++cur;
			}
			else if (mapIndex_ + 1 < container_->map_size_) {//已经在桶的结尾，但是之后还有新的map指针
				++mapIndex_;
				cur_ = getNowBuckHead(mapIndex_);//指向下一个桶的开头
			}
			else {//mapIndex_ +1之后没有了map
				mapIndex_ = container_->map_size_;

				cur_ = container_->map_[mapIndex_];//指向未知区域
			}
			return *this;
		}
		template<class T>
		deque_iterator<T> deque_iterator<T>::operator++(int){
			auto tmp = *this;
			++*this;
			return tmp;
		}
		template<class T>
		deque_iterator<T>  & deque_iterator<T>::operator--(){
			if (cur_ != getNowBuckHead(mapIndex_)) {
				--cur_;
			}
			else if (mapIndex_ - 1 >= 0) {
				--mapIndex_;
				cur_ = getNowBuckHead(mapIndex_);
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
		bool deque_iterator<T>::operator==(const deque_iterator & rhs) const{
			return ((mapIndex_ == rhs.mapIndex_)
				&& (cur_ == rhs.cur_)
				&& (container_ == rhs.container_));
		}
		template<class T>
		inline bool deque_iterator<T>::operator!=(const deque_iterator & rhs) const{
			return !(rhs == *this);
		}
		template<class T>
		deque_iterator<T> deque_iterator<T>::getNowBuckTail(size_t mapIndex)
		{
			return container_->map_[mapIndex] + (container_->getBuckSize() - 1);
		}
		template<class T>
		deque_iterator<T> deque_iterator<T>::getNowBuckHead(size_t mapIndex)
		{
			return container_->map_[mapIndex]);
		}
		template<class T>
		inline size_t deque_iterator<T>::getBuckSize(){
			return container_->getBuckSize();
		}

	}//end of Detail

	template<class T, class Alloc>
	T * deque<T, Alloc>::getANewBuck()
	{

	}
	template<class T, class Alloc>
	T ** deque<T, Alloc>::getANewMap(const size_t size){

	}
	template<class T, class Alloc>
	size_t deque<T, Alloc>::getNewMapSize(const size_t size)
	{

	}
}


#endif // !_DEQUE_DETAIL_H_
