#ifndef _LIST_H_
#define _LIST_H_
#include"alloc.h"
#include"Iterator.h"
namespace STL {
	namespace Detail {
		template <class T>
		struct __list_node {
			typedef __list_node<T>* node_pointer;
			node_pointer prev;
			node_pointer next;
			T data;
			__list_node(const T& d, __list_node* p, __list_node* n) :
				data(d), prev(p), next(n) {}
		};

		template<class T>
		struct list_iterator :public iterator<bidirectional_iterator_tag, T> {
			template<class T>
			friend class list;
		public:
			typedef __list_node<T> *nodePtr;
			nodePtr p;
		public:
			explicit list_iterator(nodePtr ptr = nullptr) :p(ptr) {}
			//²Ù×÷·ûÖØÔØ
			list_iterator& operator++();
			list_iterator operator++(int);
			list_iterator& operator --();
			list_iterator operator --(int);
			T& operator *() { return p->data; }
			T* operator ->() { return &(operator*()); }
			
			template<class T>
			friend bool operator ==(const listIterator<T>& lhs, const listIterator<T>& rhs);
			template<class T>
			friend bool operator !=(const listIterator<T>& lhs, const listIterator<T>& rhs);
		};
	}//end of Detail

	template<class T, class Alloc = alloc<T>>
	class list {
		template<class T>
		friend struct listIterator;
	private:
		typedef allocator<Detail::__list_node<T>> nodeAllocator;
		typedef Detail::__list_node<T> *nodePtr;
	public:
		typedef T value_type;
		typedef Detail::list_iterator<T> iterator;
		typedef Detail::list_iterator<const T> const_iterator;
		typedef value_type& reference;
		typedef size_t size_type;
	private:
		iterator head;
		iterator tail;
	public:
		lsit();
		
	};
}
#include"List_detail.h"
#endif // !_LIST_H_

