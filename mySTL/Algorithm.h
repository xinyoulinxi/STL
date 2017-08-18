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

	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
		_distance(InputIterator first
			, InputIterator last
			, input_iterator_tag) {
		typename iterator_traits<InputIterator>::difference_type dist = 0;
		while (first++ != last) {
			++dist;
		}
		return dist;
	}
	template<class RandomIterator>
	typename iterator_traits<RandomIterator>::difference_type
		_distance(RandomIterator first
			, RandomIterator last
			, random_access_iterator_tag) {
		auto dist = last - first;
		return dist;
	}
}

#endif