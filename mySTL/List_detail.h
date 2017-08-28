#include "List.h"
#ifndef _LIST_DETAIL_H_
#define _LIST_DETAIL_H_
namespace STL {
	namespace Detail {
		template<class T>
		list_iterator<T>& list_iterator<T>::operator ++() {
			p = p->next;
			return *this;
		}

		template<class T>
		inline list_iterator<T> list_iterator<T>::operator++(int){
			auto res = *this;
			++*this;
			return res;
		}

		template<class T>
		inline list_iterator<T>& list_iterator<T>::operator--(){
			p = p->prev;
			return *this;
		}

		template<class T>
		inline list_iterator<T> list_iterator<T>::operator--(int){
			auto res = *this;
			--*this;
			return res;
		}
		template<class T>
		bool operator==(const list_iterator<T>& lhs, const list_iterator<T>& rhs){
			return lhs.p == rhs.p;
		}
		template<class T>
		bool operator!=(const list_iterator<T>& lhs, const list_iterator<T>& rhs){
			return false;
		}
	}//end of Detail

	//                                    构造函数
	template<class T>
	inline list<T>::list()
	{
		head.p = NewNode();
		tail.p = head.p;
	}
	//__list 泛型的划分
	template<class T>
	inline list<T>::list(size_type n, const value_type & val)
	{
		__list(n, val, std::is_integral<value_type>());
	}
	template<class T>
	template <class InputIterator>
	list<T>::list(InputIterator first, InputIterator last) {
		__list(first, last, std::is_integral<InputIterator>());
	}
	template<class T>
	inline list<T>::list(const list & lis)
	{
		//__list(lis.begin(), lis, end(), std::is_integral<lis.begin()>());
		//不能直接使用

		head.p = newNode();
		tail.p = head.p;
		for (auto node = l.head.p; node != l.tail.p; node = node->next)
			push_back(node->data);
	}

	template<class T>
	inline list & list<T>::operator=(const list & rhs)
	{
		
	}
	template<class T>
	inline list<T>::~list()
	{
		for (; head != tail;) {
			auto temp = head++;
			nodeAllocator::destroy(temp.p);
			nodeAllocator::deallocate(temp.p);
		}
		nodeAllocator::deallocate(tail.p);
	}

	//                            空间配置器相关
	template<class T>
	template<class InputIterator>
	inline void list<T>::__list(InputIterator first, InputIterator last, std::false_type)
	{
		head.p = NewNode();
		tail.p = NewNode();
		for (; first != last;++first) {
			push_back(*first);
		}
	}

	template<class T>
	inline void list<T>::__list(size_type n, const value_type & val, std::true_type)
	{
		head.p = NewNode();
		tail.p = NewNode();
		while (n--) {
			push_back(val);
		}
	}


	template<class T>
	inline list<T>::nodePtr list<T>::newNode(const T& value = T())
	{
		nodePtr node = nodeAllocator::allocate();
		nodeAllocator::construct(node, Detail::__list_node<T>(value, nullptr, nullptr));
		return node;
	}
	//                         元素操作有关
	template<class T>
	void list<T>::push_front(const value_type& val) {
		auto node = newNode(val);
		head.p->prev = node;
		node->next = head.p;
		head.p = node;
	}
	template<class T>
	void list<T>::pop_front() {
		auto oldNode = head.p;
		head.p = oldNode->next;
		head.p->prev = nullptr;
		deleteNode(oldNode);
	}
	template<class T>
	void list<T>::push_back(const value_type& val) {
		auto node = newNode();
		(tail.p)->data = val;
		(tail.p)->next = node;
		node->prev = tail.p;
		tail.p = node;
	}
	template<class T>
	void list<T>::pop_back() {
		auto eraseNode = (tail.p)->next;
		eraseNode->next = nullptr;
		deleteNode(tail);
		tail.p = eraseNode;
	}
	//                  容量相关

	template<class T>
	typename list<T>::size_type list<T>::size()const {
		size_type length = 0;
		for (auto h = head; h != tail; ++h)
			++length;
		return length;
	}
}
#endif // !_LIST_DETAIL_H_

