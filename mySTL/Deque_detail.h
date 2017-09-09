#include"Deque.h"
#ifndef _DEQUE_DETAIL_H_
#define _DEQUE_DETAIL_H_
namespace STL {
	namespace Detail {
		template<class T>
		deque_iterator<T> & deque_iterator<T>::operator = (const deque_iterator & it)
		{
			if (this != &it) {
				
			}

			
		}
		template<class T>
		deque_iterator<T>  & deque_iterator<T>::operator++()
		{
			// TODO: 在此处插入 return 语句
		}
		template<class T>
		deque_iterator<T> deque_iterator<T>::operator++(int)
		{
			return deque_iterator();
		}
		template<class T>
		deque_iterator<T>  & deque_iterator<T>::operator--()
		{
			// TODO: 在此处插入 return 语句
		}
		template<class T>
		deque_iterator<T> deque_iterator<T>::operator--(int)
		{
			return deque_iterator();
		}
		template<class T>
		bool operator==(const deque_iterator<T>& lhs, const deque_iterator<T>& rhs)
		{
			return 
		}
		template<class T>
		bool operator!=(const deque_iterator<T>& lhs, const deque_iterator<T>& rhs)
		{
			return false;
		}
	}
}


#endif // !_DEQUE_DETAIL_H_
