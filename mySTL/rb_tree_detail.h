#include "rb_tree.h"
#ifndef _RB_TREE_DETAIL_H
#define _RB_TREE_DETAIL_H

namespace STL {
	namespace detail {

		template<class Value, class Ref, class Ptr>
		inline self & __rb_tree_iterator<Value, Ref, Ptr>::operator++(){
			increment();
			return *this;
		}
		template<class Value, class Ref, class Ptr>
		inline self __rb_tree_iterator<Value, Ref, Ptr>::operator++(int){
			self tmp = *this;
			increment();
			return tmp;
		}

		template<class Value, class Ref, class Ptr>
		inline self & __rb_tree_iterator<Value, Ref, Ptr>::operator--(){
			decrement();
			return *this;
		}

		template<class Value, class Ref, class Ptr>
		inline self __rb_tree_iterator<Value, Ref, Ptr>::operator--(int){
			self tmp = *this;
			decrement();
			return tmp;
		}
		
	}//end of detail
}






#endif // !_RB_TREE_DETAIL_H
