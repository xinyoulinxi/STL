#ifndef _LIST_H_
#define _LIST_H_
#include"Iterator.h"
#include"Allocator.h"
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
			//操作符重载
			list_iterator& operator++();
			list_iterator operator++(int);
			list_iterator& operator --();
			list_iterator operator --(int);
			T& operator *() { return p->data; }
			T* operator ->() { return &(operator*()); }

			template<class T>
			friend bool operator ==(const list_iterator<T>& lhs, const list_iterator<T>& rhs);
			template<class T>
			friend bool operator !=(const list_iterator<T>& lhs, const list_iterator<T>& rhs);
		};
	}//end of Detail

	template<class T>
	class list {
		template<class T>
		friend struct listIterator;
		typedef allocator<Detail::__list_node<T>> nodeAllocator;
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
		//各种构造和析构
		list();
		explicit list(size_type n, const value_type& val = value_type());
		template <class InputIterator>
		list(InputIterator first, InputIterator last);
		list(const list& lis);
		list& operator = (const list& rhs);
		~list();

	public:

		//元素访问

		reference front();
		reference back();
		iterator begin();
		iterator end();
		const_iterator begin()const;
		const_iterator end()const;

		//元素操作
		void push_front(const value_type& val);
		void pop_front();
		void push_back(const value_type& val);
		void pop_back();

		iterator insert(iterator position, const value_type& val);
		void insert(iterator position, size_type n, const value_type& val);
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);

		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		//容量相关
		void clear();

		bool empty();
		size_type size()const;
	private:
		//空间配置器相关
		nodePtr newNode();
		void deleteNode(nodePtr p);
		void __insert(iterator position, size_type n, const T& val, std::true_type);
		template<class InputIterator>
		void __insert(iterator position, InputIterator first, InputIterator last, std::false_type);
		void __list(size_type n, const value_type& val, std::true_type);
		template <class InputIterator>
		void __list(InputIterator first, InputIterator last, std::false_type);

	};




}
#include"List_detail.h"
#endif // !_LIST_H_

