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

				cur_ = container_->map_[mapIndex_];//指向最后一个桶的最后一个元素的后方区域
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
				cur_ = getNowBuckTail();
			}
			else {
				mapIndex_ = 0;
				cur_ = container_->map_[mapIndex_];
			}
			return *this;
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
		T* deque_iterator<T>::getNowBuckTail()const
		{
			return container_->map_[mapIndex_] + (container_->getBuckSize() - 1);
		}
		template<class T>
		T* deque_iterator<T>::getNowBuckHead()const
		{
			return container_->map_[mapIndex_];
		}
		template<class T>
		size_t deque_iterator<T>::getBuckSize() const {
			return container_->getBuckSize();
		}
		template<class T>
		typename deque_iterator<T>::difference_type operator -(const deque_iterator<T>& lhs
			, const deque_iterator<T>& rhs) {
			if (lhs.container_ != rhs.container_) {
				return 0;
			}
			else if (lhs.container_ == rhs.container_&&lhs.container_ == nullptr) {
				return 0;
			}
			typename deque_iterator<T>::difference_type retDis =
				typename deque_iterator<T>::difference_type(
				(lhs.mapIndex_ - rhs.mapIndex_ - 1)*lhs.getBuckSize()
					+ (lhs.cur_ - lhs.getNowBuckHead() + 1)
					+ (rhs.getNowBuckTail() - rhs.cur_)
				);
			return retDis;
		}
		template<class T>
		deque_iterator<T> operator +(const deque_iterator<T>& it
			, typename deque_iterator<T>::difference_type n) {
			deque_iterator<T> retIt(it);
			auto leftSize = retIt.getNowBuckTail() - retIt.cur_;
			if (n <= leftSize) {//前进n步后依然在当前桶内
				retIt.cur_ += n;
			}
			else {
				n -= leftSize;
				size_t newBuckIndex = n % retIt.getBuckSize() - 1;
				size_t newMapIndex = retIt.mapIndex_ + n / retIt.getBuckSize() + 1;
				retIt.mapIndex_ = newMapIndex;
				retIt.cur_ = retIt.getNowBuckHead() + newBuckIndex;
			}
			return retIt;
		}
		template<class T>
		deque_iterator<T> operator -(const deque_iterator<T>& it
			, typename deque_iterator<T>::difference_type n) {
			deque_iterator<T> retIt(it);
			auto leftSize = retIt.cur_ - retIt.getNowBuckHead();
			if (leftSize >= n) {//后退n步后依然在当前桶内
				retIt.cur_ -= n;
			}
			else {
				n -= leftSize;
				size_t newBuckIndex = n % retIt.getBuckSize() - 1;
				size_t newMapIndex = retIt.mapIndex_ + n / retIt.getBuckSize() + 1;
				retIt.mapIndex_ = newMapIndex;
				retIt.cur_ = retIt.getNowBuckHead() + newBuckIndex;
			}
			return retIt;
		}
	}//end of Detail


	//空间配置器
	template<class T, class Alloc>
	void deque<T, Alloc>::deallocateABuck(size_t index) {
		dataAllocator::deallocate(map_[index], getBuckSize());
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::__pop_front() {
		STL::destroy(start_.cur_);
		deallocateABuck(start_.mapIndex_);
		start_.mapIndex_ += 1;
		start_.cur_ = start_.getNowBuckHead();
	}
	template<class T, class Alloc>
	void  deque<T, Alloc>::__pop_back() {
		deallocateABuck(finish_.mapIndex_);
		finish_.mapIndex_ -= 1;
		finish_.cur_ = finish_.getNowBuckTail();
		STL::destroy(finish_.cur_);
	}
	template<class T, class Alloc>
	T * deque<T, Alloc>::getANewBuck() {
		return dataAllocator::allocate(getBuckSize());//未构造空间
	}
	template<class T, class Alloc>
	T**  deque<T, Alloc>::GetNewMap(const size_t& size) {
		T **map = new T*[size];
		return map;
	}
	template<class T, class Alloc>
	T ** deque<T, Alloc>::getNewMapAndGetNewBucks(const size_t& size) {
		T **map = mapAllocator::allocate(size);
		for (int i = 0; i != size; ++i) {
			map[i] = getANewBuck();
		}
		return map;
	}
	template<class T, class Alloc>
	size_t deque<T, Alloc>::getNewMapSize(const size_t size) {
		return (size == 0 ? 2 : size * 2);
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::__deque(size_t n
		, const value_type& value
		, std::true_type) {
		creat_map_and_nodes(n);
		for (int i = start_.mapIndex_; i < finish_.mapIndex_; ++i) {
			uninitialized_fill(map_[i], map_[i] + getBuckSize(), value);
		}
		//最后一个桶的构造
		uninitialized_fill(map_[finish_.mapIndex_], finish_.cur_, value);
	}
	template<class T, class Alloc>
	template<class InputIterator>
	void deque<T, Alloc>::__deque(InputIterator first
		, InputIterator last
		, std::false_type) {
		auto size = last - first;
		creat_map_and_nodes(size);
//		uninitialized_copy(first, last, start_);
		iterator indexIterator = start_;
		for (; first != last; ++first,++indexIterator) {
			STL::construct(indexIterator.cur_, *(first.cur_));
		}

	}	
	template<class T, class Alloc>
	void deque<T, Alloc>::creat_map_and_nodes(size_t num_elements) {
		//分配map节点空间
		size_type num_bucks = num_elements / getBuckSize() + 1;
		map_size_ = max(size_type(2), num_bucks + 2);
		map_ = mapAllocator::allocate(map_size_);
		size_type newStartIndex = (map_size_ - num_bucks) / 2;
		size_type newFinishIndex = newStartIndex + num_bucks - 1;
		
		for (auto i = newStartIndex; i <= newFinishIndex; ++i) {
			map_[i] = getANewBuck();
		}
		start_.mapIndex_ = newStartIndex;
		finish_.mapIndex_ = newFinishIndex;
		start_.cur_ = map_[newStartIndex];
		finish_.cur_ = map_[newFinishIndex] + num_elements % getBuckSize();
		start_.container_ = finish_.container_ = this;
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::reallocateMap(size_t nodes_to_add, bool add_at_front) {
		size_t old_num_mapNodes = finish_.mapIndex_ - start_.mapIndex_ + 1;
		size_t new_num_mapNodes = old_num_mapNodes + nodes_to_add;
		map_Pointer newStart;
		size_t newStartIndex;
		if (map_size_ > 2 * new_num_mapNodes) {//剩余map空间还有很多
			newStartIndex = (map_size_ - new_num_mapNodes) / 2
				+ (add_at_front ? nodes_to_add : 0);
			newStart = map_ + newStartIndex;
			if (newStartIndex < start_.mapIndex_) {
				STL::copy(map_ + start_.mapIndex_, map_ + finish_.mapIndex_, newStart);
			}
			else {
				STL::copy_backward(map_ + start_.mapIndex_, map_ + finish_.mapIndex_, newStart + old_num_mapNodes);
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
			STL::copy(map_ + start_.mapIndex_, map_ + finish_.mapIndex_, newStart);
			//释放原map
			mapAllocator::deallocate(map_);
			//设定新的map的地址和大小
			map_ = new_map;
			map_size_ = new_map_size;
		}
		start_ = iterator(newStartIndex, start_.cur_, this);
		finish_ = iterator(newStartIndex + old_num_mapNodes - 1, finish_.cur_, this);
	}
	template<class T, class Alloc>
	void  deque<T, Alloc>::__push_back(const value_type& value) {
		if (isBackFull()) {//map后端填满
			reallocateMap(1, false);
		}
		map_[finish_.mapIndex_ + 1] = getANewBuck();

		STL::construct(finish_.cur_, value);
		++finish_.mapIndex_;
		finish_.cur_ = finish_.getNowBuckHead();
	}
	template<class T, class Alloc>
	void  deque<T, Alloc>::__push_front(const value_type& value) {
		if (isFrontFull()) {//前方没有缓存区
			reallocateMap(1, true);
		}
		map_[start_.mapIndex_ - 1] = getANewBuck();
		--start_.mapIndex_;
		start_.cur_ = start_.getNowBuckTail();
		STL::construct(start_.cur_, value);
	}
	//元素访问
	template<class T, class Alloc>
	typename deque<T, Alloc>::reference deque<T, Alloc>::operator[] (size_type n) {
		return *(begin() + n);
	}
	template<class T, class Alloc>
	typename deque<T, Alloc>::const_reference deque<T, Alloc>::operator[] (size_type n) const {
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
	deque<T, Alloc>::deque(size_type n, const value_type & value = value_type())
		: map_size_(0), map_(nullptr) {
		__deque(n, value, typename std::is_integral<size_type>::type());
	}
	template<class T, class Alloc>
	template <class InputIterator>
	deque<T, Alloc>::deque(InputIterator first, InputIterator last)
		:map_size_(0), map_(nullptr) {
		__deque(first, last, typename std::is_integral<InputIterator>::type());
	}
	template<class T, class Alloc>
	deque<T, Alloc>::deque(const deque& rhs) {
		deque(rhs.begin(), rhs.end());
	}
	template<class T, class Alloc>
	deque<T, Alloc>::~deque() {
		clear();
		dataAllocator::deallocate(map_[start_.mapIndex_]);
		mapAllocator::deallocate(map_, map_size_);
	}

	//元素操作相关
	template<class T, class Alloc>
	void deque<T, Alloc>::push_back(const value_type& value) {
		if (empty()) {
			init();
		}
		if (finish_.cur_ != finish_.getNowBuckTail()) {
			STL::construct(finish_.cur_, value);
			++finish_;
		}
		else {
			__push_back(value);
		}

	}
	template<class T, class Alloc>
	void deque<T, Alloc>::pop_back() {
		if (finish_.cur_ != finish_.getNowBuckHead()) {//当前缓存区前端还有元素
			--finish_;
			STL::destroy(finish_.cur_);
		}
		else {
			__pop_back();
		}
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::push_front(const value_type& value) {
		if (empty()) {
			init();
		}
		if (start_.cur_ != start_.getNowBuckHead()) {
			--start_;
			STL::construct(start_.cur_, value);
		}
		else {
			__push_front(value);
		}
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::pop_front() {
		if (start_.cur_  != start_.getNowBuckTail()) {
			STL::destroy(start_.cur_);
			++start_;
		}
		else {
			__pop_front();
		}
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::clear() {
		//将除了头尾缓存区之外的所有缓存区中的元素析构（其都是饱和状态）
		for (map_Pointer node = map_ + start_.mapIndex_ + 1
			; node < map_ + finish_.mapIndex_
			; ++node) {
			STL::destroy(*node, *(node + getBuckSize()));
			dataAllocator::deallocate(*node, getBuckSize());
		}
		//释放头尾缓存区
		if (start_.mapIndex_ != finish_.mapIndex_) {//至少有头尾两个缓存区
			//析构所有头尾缓存区元素
			STL::destroy(start_.cur_, start_.getNowBuckTail());
			STL::destroy(finish_.getNowBuckHead(), finish_.cur_);
			//释放尾部缓存区，根据设计，至少需要保留一个缓存区
			dataAllocator::deallocate(map_[finish_.mapIndex_], getBuckSize());
		}
		else {//只有一个缓存区
			STL::destroy(start_.cur_, finish_.cur_);
		}
		finish_ = start_;
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
		return map_[map_size_ - 1] && end().cur_ == (map_[map_size_]);
	}
	template<class T, class Alloc>
	bool deque<T, Alloc>::isFrontFull()const {
		return map_[0] && begin().cur_ == map_[0];
	}

}


#endif // !_DEQUE_DETAIL_H_
