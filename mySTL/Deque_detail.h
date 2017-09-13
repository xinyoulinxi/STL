#include"Deque.h"
#ifndef _DEQUE_DETAIL_H_
#define _DEQUE_DETAIL_H_
namespace STL {
	namespace Detail {

		template<class T>
		deque_iterator<T>& deque_iterator<T>::operator = (const deque_iterator & it) {
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
				++cur_;
			}
			else if (mapIndex_ + 1 < container_->map_size_) {//已经在桶的结尾，但是之后还有新的map指针
				++mapIndex_;
				cur_ = getNowBuckHead();//指向下一个桶的开头
			}
			else {//mapIndex_ +1之后没有了map
				mapIndex_ = container_->map_size_;

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
		T* deque_iterator<T>::getNowBuckTail()
		{
			return container_->map_[mapIndex_] + (container_->getBuckSize() - 1);
		}
		template<class T>
		T* deque_iterator<T>::getNowBuckHead()
		{
			return container_->map_[mapIndex_];
		}
		template<class T>
		size_t deque_iterator<T>::getBuckSize() {
			return container_->getBuckSize();
		}

	}//end of Detail


	//空间配置器
	template<class T, class Alloc>
	T * deque<T, Alloc>::getANewBuck(){
		return dataAllocator::allocate(getBuckSize());//未构造空间
	}
	template<class T, class Alloc>
	T**  deque<T, Alloc>::GetNewMap(const size_t& size) {
		T **map = new T*[size];
		return map;
	}
	template<class T, class Alloc>
	T ** deque<T, Alloc>::getNewMapAndGetNewBucks(const size_t size){
		T **map = new T*[size];
		for (int i = 0; i != size; ++i) {
			map[i] = getANewBuck();
		}
		return map;
	}
	template<class T, class Alloc>
	size_t deque<T, Alloc>::getNewMapSize(const size_t size){
		return (size == 0 ? 2 : size * 2);
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::__deque(size_t n
		, const value_type& value
		, std::true_type) {
		reallocateMap(n);
		size_t num = n;
		auto it = begin();
		while (num--) {
			
		}
	}
	template<class T, class Alloc>
	template<class Iterator>
	void deque<T, Alloc>::__deque(Iterator first
		, Iterator last
		, std::false_type) {

	}
	template<class T, class Alloc>
	void deque<T, Alloc>::reallocateMap(size_t nodes_to_add, bool add_at_front) {
		//size_t newMapSize = getNewMapSize(
		//	map_size_ > nodes_to_add ?
		//	map_size_, nodes_to_add);
		//auto newMap = get(newMapSize);
		//size_t startIndex = newMapSize / 4;
		size_t old_num_mapNodes = finish_.mapIndex_ - start_.mapIndex_ + 1 ;
		size_t new_num_mapNodes = old_num_mapNodes + nodes_to_add;
		 
		map_Pointer newStart;
		size_t newStartIndex;
		if (map_size_ > 2 * new_num_mapNodes) {//剩余map空间还有很多
			newStartIndex = (map_size_ - new_num_mapNodes) / 2
				+ (add_at_front ? nodes_to_add : 0);
			newStart = map_ + newStartIndex;
			if (newStartIndex < start_.mapIndex_) {
				copy(map_+start_.mapIndex_
					, map_+finish_.mapIndex_
					, newStart);
			}
			else {
				copy_backward(map_ + start_.mapIndex_
					, map_+ finish_.mapIndex_
					, newStart + old_num_mapNodes);
			}
		}
		else {
			size_t new_map_size = map_size_ + max(map_size_, nodes_to_add) + 2;
			//配置新map空间
			map_Pointer new_map = GetNewMap(new_map_size);
			newStartIndex = (new_map_size - new_num_mapNodes) / 2
				+ (add_at_front ? nodes_to_add : 0);
			newStart = new_map + newStartIndex;
			//复制原map的内容
			copy(map_ + start_.mapIndex_, map_ + finish_.mapIndex_, newStart);
			//释放原map
			delete [] map_;
			//设定新的map的地址和大小
			map_ = new_map;
			map_size_ = new_map_size;
		}
		//设定新的start和finish地址
		start_ = iterator(newStartIndex
			,*newStart
			,this);
		finish_ = iterator(newStartIndex + old_num_mapNodes - 1
			,*(newStart+old_num_mapNodes-1)
			,this);
		
	}
	//元素访问
	template<class T, class Alloc>
	typename deque<T, Alloc>::reference deque<T, Alloc>::operator[] (size_type n) {
		return *(begin() + n);
	}
	template<class T, class Alloc>
	typename deque<T, Alloc>::reference deque<T, Alloc>::front() {
		return *begin();
	}
	template<class T, class Alloc>
	typename deque<T, Alloc>::reference deque<T, Alloc>::back() {
		return *(end() - 1);
	}
	//构造函数相关
	template<class T, class Alloc>
	deque<T, Alloc>::deque()
		:map_size_(0), map_(nullptr) {
	}
		
	template<class T, class Alloc>
	deque<T, Alloc>::deque(size_t n, const value_type & value = value_type()) 
		: map_size_(0), map_(nullptr) {
		__deque(n, value, typename std::is_integral<size_type>::type());
		
	}
	template<class T, class Alloc>
	
	template <class InputIterator>
	deque<T, Alloc>::deque(InputIterator first, InputIterator last)
		:mapSize_(0), map_(nullptr) {
		__deque(first, last, typename std::is_integral<size_type>::type());
	}
	template<class T, class Alloc>
	deque<T, Alloc>::deque(const deque& rhs) {

	}
	template<class T, class Alloc>
	deque<T, Alloc>::~deque() {
	}

	//元素操作相关
	template<class T, class Alloc>
	void deque<T, Alloc>::push_back(const value_type& value) {
		if (empty()) {
			init();
		}
		else if (isBackFull()) {
			reallocateMap(1,false);
		}
		STL::construct(finish_.cur_, value);
		++finish_;
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::pop_back() {
		--finish_;
		STL::destory(finish_.cur_);
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::push_front(const value_type& value) {
		if (empty()) {
			init();
		}
		else if (isFrontFull()) {
			reallocateMap(1,false);
		}
		--start_;
		STL::construct(start_.cur_, value);

	}
	template<class T, class Alloc>
	void deque<T, Alloc>::pop_front() {

	}
	template<class T, class Alloc>
	void deque<T, Alloc>::clear() {
		for (auto i = 0; i != map_size_; ++i) {
			for (auto p = map_[i] + 0; !p && p != map_[i] + getBuckSize(); ++p) {
				dataAllocator::destroy(p);
			}
		}
		map_size_ = 0;
		start_.mapIndex_ = finish_.mapIndex_ = 0;
		start_.cur_ = finish_.cur_ = nullptr;
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::init() {
		map_size_ = 2;
		map_ = getNewMapAndGetNewBucks(map_size_);
		//将起始点放置在中间
		start_.container_ = finish_.container_ = this;
		start_.mapIndex_ = finish_.mapIndex_ = map_size_ - 1;
		start_.cur_ = finish_.cur_ = map_[map_size_ - 1];
	}
	template<class T, class Alloc>
	bool deque<T, Alloc>::isBackFull()const {
		return map_[map_size_ - 1] && end().cur_ == map_[map_size_ - 1] + getBuckSize();
	}
	template<class T, class Alloc>
	bool deque<T, Alloc>::isFrontFull()const {
		return map_[0] && begin().cur_ == map[0];
	}
	
}


#endif // !_DEQUE_DETAIL_H_
