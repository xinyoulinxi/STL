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
		inline list_iterator list_iterator<T>::operator++(int){
			auto res = *this;
			++*this;
			return res;
		}

		template<class T>
		inline list_iterator& list_iterator<T>::operator--(){
			p = p->prev;
			return *this;
		}

		template<class T>
		inline list_iterator list_iterator<T>::operator--(int){
			auto res = *this;
			--*this;
			return res;
		}
		template<class T>
		bool operator==(const listIterator<T>& lhs, const listIterator<T>& rhs){
			return lhs.p == rhs.p;
		}
		template<class T>
		bool operator!=(const listIterator<T>& lhs, const listIterator<T>& rhs){
			return false;
		}
	}
}
#endif // !_LIST_DETAIL_H_

