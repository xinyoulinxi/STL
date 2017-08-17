#ifndef _UNINITIALIZED_FUNC
#define _UNINITIALIZED_FUNC
#include"type_traits.h"
#include"Construct.h"
#include"Algorithm.h"
namespace STL {
	
	/******************  uninitialized_fill() ************/
	template<class ForwardIterator , class T>
	void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value) {
		typedef typename __type_traits<T>::is_POD_type is_POD;
		__uninitialized_fill(first, last, value, is_POD());

	}
	template<class ForwardIterator, class T>
	void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T&value, __true_type) {
		fill(first, last, value);
	}
	template<class ForwardIterator, class T>
	void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value,__false_type ) {
		for (; first != last; ++first) {
			construct(first, value);
		}
	}
	/******************  uninitialized_fill_n()  ************/
	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first,
		Size n, const T& value, _true_type);
	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first,
		Size n, const T& value, _false_type);

	template<class ForwardIterator, class Size, class T>
	inline ForwardIterator uninitialized_fill_n(ForwardIterator first,
		Size n, const T& value) {
		typedef typename _type_traits<T>::is_POD_type isPODType;
		return _uninitialized_fill_n_aux(first, n, value, isPODType());
	}
	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first,
		Size n, const T& value, _true_type) {
		return fill_n(first, n, value);
	}
	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first,
		Size n, const T& value, _false_type) {
		for (; n>0; --n,++first) {
			construct((T*)first, value);
		}
		return first;
	}
}


#endif // !_UNINITIALIZED_FUNC
