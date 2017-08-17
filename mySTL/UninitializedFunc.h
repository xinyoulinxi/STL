#ifndef _UNINITIALIZED_FUNC
#define _UNINITIALIZED_FUNC
#include"type_traits.h"
#include"Construct.h"
#include"Algorithm.h"
namespace STL {
	
	/******************  uninitialized_fill_n  ************/
	template<class ForwardIterator , class T>
	void uninitialized_fill_n(ForwardIterator first, ForwardIterator last, const T& value) {
		typedef typename __type_traits<T>::is_POD_type is_POD;
		__uninitialized_fill(first, last, value, is_POD());

	}
	template<class ForwardIterator, class T>
	void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T&value, __true_type) {
		fill(first, last, value);
	}
	template<class ForwardIterator, class T>
	void __uninitialized_fill_n(ForwardIterator first, ForwardIterator last, const T& value,__false_type ) {
		for (; first != last; ++first) {
			construct(first, value);
		}
	}

}


#endif // !_UNINITIALIZED_FUNC
