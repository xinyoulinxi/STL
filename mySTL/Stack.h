#ifndef _STACK_H_
#define _STACK_H_
#include"Vector.h"

namespace STL {
	template<class T, class Container = STL::vector<T>>
	class stack {
	public:
		typedef typename Container::value_type value_type;
		typedef typename Container::reference reference;
		typedef typename Container::size_type size_type;
		typedef Container container_type;
	private:
		container_type container_;
	public:
		explicit stack(container_type con= container_type()) :container_(con) {}
		void pop() { container_.erase(container_.end() - 1); }
		void push(const value_type&value) { container_.push_back(value); }
		size_type size() { return container_.size(); }
		bool empty() { return container_.empty(); }
		reference top() { return container_.back(); }
		const reference top() const{ return container_.back(); }

	public:
		template <class T, class Container>
		friend bool operator ==(const stack<T, Container>& lhs, const stack<T, Container>& rhs);
		template <class T, class Container>
		friend bool operator!= (const stack<T, Container>& lhs, const stack<T, Container>& rhs);

	};
	
	template<class T, class Container>
	bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return lhs.container_ == rhs.container_;
	}

	template<class T, class Container>
	bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return lhs.container_ != rhs.container_;
	}

}

#endif // !_STACK_H