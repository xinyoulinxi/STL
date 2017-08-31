#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_
#include<cstring>
#include"Iterator.h"
#include<assert.h>
#include"type_traits.h"
namespace STL {
	/**********************              fill()     ***********************************
	**************************** Algorithm Complexity  O(N)  ******************************/ 

	template<class ForwardIterator, class T>
	void fill(ForwardIterator first, ForwardIterator last, const T& value)
	{
		for (; first != last; ++first)
			*first = value;
	}
	inline void fill(char *first, char *last, const char& value)
	{
		memset(first, static_cast<unsigned char>(value), last - first);
	}
	inline void fill(wchar_t *first, wchar_t *last, const wchar_t& value)
	{
		memset(first, static_cast<unsigned char>(value), (last - first) * sizeof(wchar_t));
	}

	/**********************              fill_n()     ***********************************
	**************************** Algorithm Complexity  O(N)  ******************************/

	template<class Iterator, class Size, class T>
	Iterator fill_n(Iterator first, Size n, const T& value)
	{
		for (; n > 0; --n, ++first)
			*first = value;
		return first;
	}
	template<class Size>
	char *fill_n(char *first, Size n, const char& value)
	{
		memset(first, static_cast<unsigned char>(value), n);
		return first + n;
	}
	template<class Size>
	wchar_t *fill_n(wchar_t *first, Size n, const wchar_t& value)
	{
		memset(first, static_cast<unsigned char>(value), n * sizeof(wchar_t));
		return first + n;
	}
	//********************        distance()          ******************************
	//****************      Algorithm Complexity: O(N) *******************

	//整个的distance函数
	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
		__distance(InputIterator first
			, InputIterator last
			, input_iterator_tag) {
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (first++ != last) {
			++n;
		}
		return n;
	}
	template<class RandomIterator>
	typename iterator_traits<RandomIterator>::difference_type
		__distance(RandomIterator first
			, RandomIterator last
			, random_access_iterator_tag) {
		return (last - first);
	}

	template<class Iterator>
	typename iterator_traits<Iterator>::difference_type
		distance(Iterator first, Iterator last) {
		typedef typename iterator_traits<Iterator>::iterator_category category;
		return __distance(first, last, category());
	}
	//先使用std自带的泛型函数
	////********************      copy_backward()       ******************************
	////****************      Algorithm Complexity: O(N) ****************************

	template< class BidirIt1, class BidirIt2 >
	BidirIt2 copy_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last){
		while (first != last) {
			*(--d_last) = *(--last);
		}
		return d_last;
	}
	//********************              copy()         ***************************************
	//****************      Algorithm Complexity: O(N) ****************************

	template<class InputIt, class OutputIt>
	OutputIt copy(InputIt first, InputIt last,
		OutputIt d_first)
	{
		while (first != last) {
			*d_first++ = *first++;
		}
		return d_first;
	}

	//********************        max()          ******************************
	//****************      Algorithm Complexity: O(1) ****************************
	template <class T>
	const T& max(const T& a, const T& b) {
		return (a < b) ? b : a;
	}
	template <class T, class Compare>
	const T& max(const T& a, const T& b, Compare comp) {
		return (comp(a, b)) ? b : a;
	}
	//********************        min()          ******************************
	//****************      Algorithm Complexity: O(1)****************************
	template <class T>
	const T& min(const T& a, const T& b) {
		return !(b < a) ? a : b;
	}
	template <class T, class Compare>
	const T& min(const T& a, const T& b, Compare comp) {
		return !comp(b, a) ? a : b;
	}
	//********************       find()          ******************************
	//****************      Algorithm Complexity: O(1)****************************

	template<class InputIterator,class T>
	InputIterator find(InputIterator first, InputIterator last, const T& value) {
		while (first != last&&*first != value) {
			++first;
		}
		return first;
	}
	//********************       find_if()          ******************************
	//****************      Algorithm Complexity: O(1) ****************************

	template<class InputIterator, class T,class Func>
	InputIterator find(InputIterator first, InputIterator last, const T& value,Func isFunc) {
		while (first != last&&!isFunc(value,first)) {
			++first;
		}
		return first;
	}
	//********************       accumulate()        ******************************
	//****************      Algorithm Complexity: O(1) ****************************
	template<class InputIterator, class T>
	InputIterator find(InputIterator first, InputIterator last, T init) {
		for (; first != last; ++first) {
			init = init + *first;
		}
		return init;
	}
	template<class InputIterator, class T, class BinaryOperation>
	InputIterator find(InputIterator first, InputIterator last, T init, BinaryOperation binary_op) {
		for (; first != last; ++first) {
			init = binary_op(init, *firs);//对每个元素执行二元操作
		}
		return init;
	}
	//********************       iter_swap()        ******************************
	//****************      Algorithm Complexity: O(1) ****************************
	template<class InputIterator1, class InputIterator2>
	inline void iter_swap(InputIterator1 itL, InputIterator1 itR) {
		__iter_swap(itL, itR, value_type(itL));
	}
	template<class InputIterator1, class InputIterator2,class T>
	inline void __iter_swap(InputIterator1 itL, InputIterator1 itR,T*) {
		T tmp = *itL;
		*itL = *itR;
		*itR = tmp;
	}
	//也可直接这样书写
	//template<class InputIterator1, class InputIterator2>
	//inline void iter_swap(InputIterator1 itL, InputIterator1 itR) {
	//	typename iterator_traits<InputIterator1>::value_type tmp = *itL;
	//	*itL = *itR;
	//	*itR = tmp;

	//}
	
}

#endif