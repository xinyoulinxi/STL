#pragma once
#ifndef _REVERSE_ITERATOR_H_
#define _REVERSE_ITERATOR_H_
#include"Iterator.h"
namespace STL {
	template<class Iterator>
	class reverse_iterator {

	public:
		//标准型别类型
		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef const pointer const_pointer;
		typedef typename iterator_traits<Iterator>::reference reference;
		typedef const reference const_reference;
		

	private:
		
	};
}

#endif