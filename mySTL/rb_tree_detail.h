#include "rb_tree.h"
#ifndef _RB_TREE_DETAIL_H
#define _RB_TREE_DETAIL_H

namespace STL {
	template<class Value, class Ref, class Ptr>
	typename __rb_tree_iterator<Value, Ref, Ptr>::self & __rb_tree_iterator<Value, Ref, Ptr>::operator++() {
		increment();
		return *this;
	}
	template<class Value, class Ref, class Ptr>
	typename __rb_tree_iterator<Value, Ref, Ptr>::self __rb_tree_iterator<Value, Ref, Ptr>::operator++(int) {
		self tmp = *this;
		increment();
		return tmp;
	}

	template<class Value, class Ref, class Ptr>
	typename __rb_tree_iterator<Value, Ref, Ptr>::self & __rb_tree_iterator<Value, Ref, Ptr>::operator--() {
		decrement();
		return *this;
	}

	template<class Value, class Ref, class Ptr>
	typename __rb_tree_iterator<Value, Ref, Ptr>::self __rb_tree_iterator<Value, Ref, Ptr>::operator--(int) {
		self tmp = *this;
		decrement();
		return tmp;
	}
	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::link_type
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::create_node(const value_type & x) {
		link_type tmp = get_node();
		construct(&tmp->value_field, x);
		return tmp;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::link_type
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::clone_node(link_type x)
	{
		return link_type();
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	inline void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::destroy_node(link_type p) {
		destroy(&p->value_field);
		put_node(p);
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::
		__insert(base_ptr x_, base_ptr y_, const value_type & v) {
		link_type x = link_type(x_);
		link_type y = link_type(y_);
		link_type z;
		if (y == header || x != 0 || key_compare(KeyOfValue()(v), Key(y))) {
			z = create_node(v);
			left(y) = z;
			if (y == header) {
				root() = z;
				rightmost() = z;
			}
			else if (leftmost() == y) {//如果y为最左节点
				leftmost() = z;          //令新插入节点为最左节点
			}
		}
		else {
			z = create_node(v);
			right(y) = z;
			if (rightmost() == y) {
				rightmost() = z;
			}
		}
		parent(z) = y;
		left(z) = 0;
		right(z) = 0;
		__rebalance_rb_tree(z, header->parent);
		++node_count;
		return iterator(z);
	}
	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::link_type
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::__copy(link_type x, link_type p) {
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
		value(header) = 0;
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
	inline typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(const Value & V) {

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
	inline  typename pair<typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator, bool>
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(const Value & v) {
		link_type y = header;
		link_type x = root();
		bool comp = true;
		while (x != 0) {//从根节点开始寻找适当的叶子节点进行插入
			y = x;
			comp = key_compare(KeyOfValue()(v), key(x));
			x = comp ? left(x) : right(x);
		}
		//此时y为插入点的父节点
		iterator j = iterator(y);
		if (comp) {//如果离开while循环时comp为真，则表示插入点在y的左侧
			if (begin()==j ) {//如果插入点的父节点为最左节点
				return pair<iterator, bool>(__insert(x, y, v), true);
			}
			else {//否则
				//调节j节点
				--j;
			}
		}
		if (key_compare(key(j.node), KeyOfValue()(v))) {
			//新键值不与既有节点之键值重复,执行安插操作
			return pair<iterator, bool>(__insert(x, y, v), true);
		}
		//进行到此处，表示新值一定与树中的某个键值重复，那么就不进行插入
		return pair<iterator, bool>(j, false);
	}
	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	inline void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::
		__single_rotate_left(__rb_tree_node_base * x, __rb_tree_node_base *& root) {
		//X为旋转点
		__rb_tree_node_base* y = x->right;//y为旋转点的右子节点
		x->right = y->left;               //调整x的左子节点
		if (y->left != 0)                 //若y有左子节点
			y->left->parent = x;          //调整这个左子节点的父节点为x
		y->parent = x->parent;            //调整y的父节点指向y的祖父节点
		if (x == root) {                  //x为根节点
			root = y;
		}
		else if (x == x->parent->left) { //x为其父节点的左子节点
			x->parent->left = y;
		}
		else {                           //x为其父节点的右子节点
			x->parent->right = y;
		}
		//调整旋转点自身的连接情况
		y->left = x;
		x->parent = y;
	}
	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	inline void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::
		__single_rotate_right(__rb_tree_node_base * x, __rb_tree_node_base *& root) {
		//同__single_rotate_left
		__rb_tree_node_base* y = x->left;
		x->left = y->right;
		if (y->right != 0)
			y->right->parent = x;
		y->parent = x->parent;
		if (x == root) {
			root = y;
		}
		else if (x == x->parent->right) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}
	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	inline void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::
		__rebalance_rb_tree(__rb_tree_node_base * x, __rb_tree_node_base *& root) {
		x->color = __rb_tree_red;    //新节点为红
		while (x != root && x->parent->color == __rb_tree_red) {  //父节点为红
			if (x->parent == x->parent->parent->left) {           //父节点是祖父节点的左子节点
				__rb_tree_node_base* y = x->parent->parent->right;//y为伯父节点（伯父节点指父节点的兄弟节点）
				if (y && y->color == __rb_tree_red) {             //（情况一）—— 伯父节点存在，且为红（且父节点是祖父节点的左子节点）
					x->parent->color = __rb_tree_black;           //更改父节点为黑
					y->color = __rb_tree_black;                   //调整伯父节点为黑
					x->parent->parent->color = __rb_tree_red;     //调整祖父节点为红
					x = x->parent->parent;                        //调整节点，向上继续进行颜色调整
				}
				else { //无伯父节点 ,或伯父节点为黑色                         
					if (x == x->parent->right) { //（情况二）如果新节点为父节点的右子节点，且父节点是祖父节点的左子节点（进行双旋）
						x = x->parent;
						__single_rotate_left(x, root);//以插入点的父节点为左旋转点进行左旋
					}
					//（情况三）若新节点为父节点的右子节点，且父节点是祖父节点的左子节点（进行单旋转）
					//颜色调整
					x->parent->color = __rb_tree_black;
					x->parent->parent->color = __rb_tree_red;
					__single_rotate_right(x->parent->parent, root);
				}
			}
			else {        //父节点为祖父节点的左子节点
				__rb_tree_node_base* y = x->parent->parent->left;//y为伯父节点
				if (y && y->color == __rb_tree_red) {            //（情况四）有伯父节点，且为红，且父节点为祖父节点的左子节点（进行双旋）
					x->parent->color = __rb_tree_black;          //更改父节点颜色为黑
					y->color = __rb_tree_black;                  //更改伯父节点为黑
					x->parent->parent->color = __rb_tree_red;    //更改祖父节点为红
					x = x->parent->parent;                       //向上继续进行调整
				}
				else {//       无伯父节点，或则伯父节点为黑
					if (x == x->parent->left) {   //（情况五）如果新节点为父节点的左子节点，且父节点为祖父节点的左子节点（此时进行双旋）
						x = x->parent;
						__single_rotate_right(x, root);//以插入点的父节点为右旋点进行右旋
					}
					//（情况六）如果新节点为父节点的左子节点（执行单旋转）
					x->parent->color = __rb_tree_black;
					x->parent->parent->color = __rb_tree_red;
					__single_rotate_left(x->parent->parent, root);//左旋
				}
			}
		}// end of while
		root->color = __rb_tree_black;//根节点永远为黑
	}
}





#endif // !_RB_TREE_DETAIL_H
