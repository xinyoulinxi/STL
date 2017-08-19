#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_
#include<cstring>
#include"Iterator.h"
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
		return (last - first;)
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

	//template< class BidirIt1, class BidirIt2 >
	//BidirIt2 copy_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last){
	//	while (first != last) {
	//		*(--d_last) = *(--last);
	//	}
	//	return d_last;
	//}
	////********************              copy()                 ***************************************
	////****************      Algorithm Complexity: O(N) ****************************

	//template<class InputIt, class OutputIt>
	//OutputIt copy(InputIt first, InputIt last,
	//	OutputIt d_first)
	//{
	//	while (first != last) {
	//		*d_first++ = *first++;
	//	}
	//	return d_first;
	//}
}

#endif