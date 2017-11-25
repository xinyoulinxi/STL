#ifndef _RB_TREE_H_
#define _RB_TREE_H_
#include"Iterator.h"
#include<new>
namespace STL {
	namespace detail {

		typedef bool __rb_tree_color_type;
		const __rb_tree_color_type __rb_tree_red = false;   //红色  0
		const __rb_tree_color_type __rb_tree_black = true;  //黑色  1

		//红黑树的节点基类
		struct __rb_tree_node_base {
			typedef __rb_tree_color_type color_type;
			typedef __rb_tree_node_base* base_ptr;

			color_type   color;
			base_ptr     parent;
			base_ptr     left;
			base_ptr     right;
			static base_ptr minmun(base_ptr x) {//寻找最小值
				while (nullptr != x->left)x = x->left;
				return x;
			}
			static base_ptr maxmum(base_ptr x) {//寻找最大值
				while (nullptr != x->right)x = x->right;
				return x;
			}
		};

		//红黑树的节点
		template<class Value>
		struct  __rb_tree_node :public __rb_tree_node_base {
			typedef __rb_tree_node<Value>* link_type;
			Value value_field;   //节点值
		};


		//红黑树迭代器设计
			//迭代器基类
		struct __rb_tree_base_iterator
		{
			typedef __rb_tree_node_base*                base_ptr;
			typedef STL::bidirectional_iterator_tag     iterator_category;
			typedef ptrdiff_t                           defference;

			base_ptr  node;
			void increment() {
				if (nullptr != node->right) {                //如果有右子节点
					node = node->right;                      //就向右走
					while (nullptr != node->left) {          //然后一直往左到底
						node = node->left;
					}
				}
				else {                                        //没有右子节点
					base_ptr y = node->parent;               //找出父节点
					while (node == y->right) {               //上溯
						node = y;
						y = y->parent;
					}
					if (node->right != y) {
						node = y;
					}
				}
			}
			void decrement() {
				if (node->color == __rb_tree_red &&
					node->parent->parent == node)
					node = node->right;
				else if (node->left != 0) {
					base_ptr y = node->left;
					while (y->right != 0)
						y = y->right;
					node = y;
				}
				else {
					base_ptr y = node->parent;
					while (node == y->left) {
						node = y;
						y = y->parent;
					}
					node = y;
				}
			}
		};

		//红黑树的迭代器
		template<class Value, class  Ref, class Ptr>
		struct __rb_tree_iterator :public __rb_tree_base_iterator {
			//正常typedef
			typedef Value      value_type;
			typedef Ref        reference;
			typedef Ptr        pointer;
			typedef __rb_tree_iterator<Value, Value&, Value*>             iterator;
			typedef __rb_tree_iterator<Value, const Value&, const Value*> const_iterator;
			typedef __rb_tree_iterator<Value, Ref, Ptr>                   self;
			typedef __rb_tree_node<Value>* link_type;

			__rb_tree_iterator() {}
			__rb_tree_iterator(link_type x) { node = x; }
			__rb_tree_iterator(const iterator& it) { node = it.node; }

			//符号重载
			pointer operator->() const { return &(operator*()); }
			reference operator*() const { return link_type(node)->value_field; }
			self& operator++();
			self operator++(int);
			self& operator--();
			self operator--(int);
			
		};

	}//end of detail 
}
//实现细节
#include"rb_tree_detail.h"

#endif // !_RB_TREE_H_

