#ifndef _QUEUE_H_
#define _QUEUE_H_
#include"Deque.h"
namespace STL {
	template<class T,class Container=STL::deque<T>>
	class queue {
	public:
		typedef T                   value_type;
		typedef value_type*          pointer;
		typedef pointer              iterator;
		typedef value_type&           reference;
		typedef const reference      const_reference;
		typedef  size_t           size_type;
		typedef Container       container_type;
	private:
		container_type container_;
	public:
		queue(container_type conr = container_type()) :container_(conr) {}
		template<class InputIterator>
		queue(InputIterator first, InputIterator last) : container_(first, last) {}
		queue(const queue& rhs) : container_(rhs.container_) {}
		queue(const queue&& rhs) :container_(rhs.container_) {}
		
		reference front();
		reference back();
		const_reference front()const;
		const_reference back()const;
		void push(const value_type& value);
		void pop();
		bool empty()const;
		size_type size()const;

	};
	template<class T, class Container>
	inline queue<T, Container>::reference queue<T, Container>::front()
	{
		return container_.front();
	}
	template<class T, class Container>
	inline queue<T, Container>::reference queue<T, Container>::back()
	{
		return container_.back();
	}
	template<class T, class Container>
	inline queue<T, Container>::const_reference queue<T, Container>::front() const
	{
		return container_.front();
	}
	template<class T, class Container>
	inline queue<T, Container>::const_reference queue<T, Container>::back() const
	{
		return container_.back();
	}
	template<class T, class Container>
	inline void queue<T, Container>::push(const value_type& value)
	{
		container_.push_back(value);
	}
	template<class T, class Container>
	inline void queue<T, Container>::pop()
	{
		container_.pop_front();
	}
	template<class T, class Container>
	inline bool queue<T, Container>::empty() const
	{
		return container_.empty();
	}
	template<class T, class Container>
	inline queue<T, Container>::size_type queue<T, Container>::size() const
	{
		return container_.size();
	}
}
#endif // !_QUEUE_H_

