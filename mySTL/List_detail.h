#include "List.h"
#ifndef _LIST_DETAIL_H_
#define _LIST_DETAIL_H_
namespace STL {
	namespace Detail {
		template<class T>
		list_iterator<T>& list_iterator<T>::operator ++() {
			p = p->next;
			return *this;
		}

		template<class T>
		inline list_iterator<T> list_iterator<T>::operator++(int){
			auto res = *this;
			++*this;
			return res;
		}

		template<class T>
		inline list_iterator<T>& list_iterator<T>::operator--(){
			p = p->prev;
			return *this;
		}

		template<class T>
		inline list_iterator<T> list_iterator<T>::operator--(int){
			auto res = *this;
			--*this;
			return res;
		}
		template<class T>
		bool operator==(const list_iterator<T>& lhs, const list_iterator<T>& rhs){
			return lhs.p == rhs.p;
		}
		template<class T>
		bool operator!=(const list_iterator<T>& lhs, const list_iterator<T>& rhs){
			return false;
		}
	}//end of Detail
}
#endif // !_LIST_DETAIL_H_

