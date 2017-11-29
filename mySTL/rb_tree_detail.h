#include "rb_tree.h"
#ifndef _RB_TREE_DETAIL_H
#define _RB_TREE_DETAIL_H

namespace STL {
	namespace detail {

		template<class Value, class Ref, class Ptr>
		self & __rb_tree_iterator<Value, Ref, Ptr>::operator++() {
			increment();
			return *this;
		}
		template<class Value, class Ref, class Ptr>
		self __rb_tree_iterator<Value, Ref, Ptr>::operator++(int) {
			self tmp = *this;
			increment();
			return tmp;
		}

		template<class Value, class Ref, class Ptr>
		self & __rb_tree_iterator<Value, Ref, Ptr>::operator--() {
			decrement();
			return *this;
		}

		template<class Value, class Ref, class Ptr>
		self __rb_tree_iterator<Value, Ref, Ptr>::operator--(int) {
			self tmp = *this;
			decrement();
			return tmp;
		}

	}//end of detail

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	link_type rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::create_node(const value_type & x) {
		link_type tmp = get_node();
		construct(&tmp->value_field, x);
		return tmp;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	link_type rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::clone_node(link_type x)
	{
		return link_type();
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	inline void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::destroy_node(link_type p) {
		destroy(&p->value_field);
		put_node(p);
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	iterator rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::
		__insert(base_ptr x, base_ptr y, const value_type & v) {

	}
	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	link_type rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::__copy(link_type x, link_type p) {
		link_type top = clone_node(x);
		top->parent = p;
		if (x->right)
			top->right = __copy(right(x), top);
		p = top;
		x = left(x);

		while (x != 0) {
			link_type y = clone_node(x);
			p->left = y;
			y->parent = p;
			if (x->right)
				y->right = __copy(right(x), y);
			p = y;
			x = left(x);
		}
		return top;
	}
	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::__erase(link_type x) {
		// 删除节点，但不重新调节树
		while (x != 0) {
			__erase(right(x));
			link_type y = left(x);
			destroy_node(x);
			x = y;
		}
	}
	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::init() {
		//将header的父指向和左右节点都指向自身
		header = get_node();
		color(header) = __rb_tree_red;
		root() = 0;
		leftmost() = header;
		rightmost() = header;
	}
	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::rb_tree(const Compare & comp)
		: node_count(0)
		, key_compare(comp) {
		init();
	}
	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::rb_tree(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x)
		: node_count(0)
		, key_compare(x.key_compare)
	{
		header = get_node();
		color(header) = __rb_tree_red;
		if (x.root() == 0) {
			root() = 0;
			leftmost() = header;
			rightmost() = header;
		}
		else {
			root() = __copy(x.root(), header);
			leftmost() = minimum(root());
			rightmost() = maximum(root());
		}
		node_count = x.node_count;
	}
	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::~rb_tree()
	{
	}
	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::
		operator = (const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x)
	{
		// TODO: 在此处插入 return 语句
	}

	//允许节点键值重复的插入操作
	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	inline rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(const Value & V) {

		link_type x = header;
		link_type y = root();
		while (x != 0) {//从根节点开始寻找适当的叶子节点进行插入
			y = x;
			x = key_compare(KeyOfValue()(v), key(x)) ? left(x) : right(x);
			//遇到‘大’的则向左，‘小或者等于的’则向右
		}
		return __insert(x, y, v);
	}

	//不允许节点键值重复的插入操作，若重复则无效
	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(const Value & V) {
		link_type x = header;
		link_type y = root();
		bool comp = true;
		while (x != 0) {//从根节点开始寻找适当的叶子节点进行插入
			y = x;
			comp = key_compare(KeyOfValue()(v), key(x))
				x = comp ? left(x) : right(x;
		}
		//此时y为插入点的父节点
		iterator j = iterator(y);
		if (comp) {//如果离开while循环时comp为真，则表示插入点在y的左侧
			if (j == begin()) {//如果插入点的父节点为最左节点
				return pair<iterator, bool>(__insert(x, y, v), true);
			}
			else {//否则
				//调节j节点
				--j;
			}
		}
		if (key_compare(key(j.node), KeyOfValue()(v)) {
			//新键值不与既有节点之键值重复,执行安插操作
			return pair<iterator, bool>(__insert(x, y, v), true);
		}
		//进行到此处，表示新值一定与树中的某个键值重复，那么就不进行插入
		return pair<iterator, bool>(j, true);
	}
}






#endif // !_RB_TREE_DETAIL_H
