#ifndef _RB_TREE_H_
#define _RB_TREE_H_
#include"Iterator.h"
#include"Allocator.h"
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
			static base_ptr minimun(base_ptr x) {//寻找最小值
				while (nullptr != x->left)x = x->left;
				return x;
			}
			static base_ptr maximum(base_ptr x) {//寻找最大值
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
					base_ptr y = node->parent;                //找出父节点
					while (node == y->right) {                //上溯
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
	template <class Key, class Value, class KeyOfValue, class Compare,
		class Alloc = alloc>
		class rb_tree {
		protected:
			typedef void*                                       void_pointer;
			typedef  __rb_tree_node_base*                       base_ptr;
			typedef __rb_tree_node<Value>                       rb_tree_node;
			typedef STL::allocator<rb_tree_node, Alloc>         rb_tree_node_allocator;
			typedef __rb_tree_color_type                        color_type;

		public:
			typedef Key                key_type;
			typedef Value              value_type;
			typedef value_type*        pointer;
			typedef const value_type*  const_pointer;
			typedef value_type&        reference;
			typedef const value_type&  const_reference;
			typedef rb_tree_node*      link_type;
			typedef size_t             size_type;
			typedef ptrdiff_t          difference_type;

		protected:
			link_type get_node() { return rb_tree_node_allocator::allocate(); }
			void put_node(link_type p) { rb_tree_node_allocator::deallocate(p); }
			link_type create_node(const value_type& x);
			link_type clone_node(link_type x);
			void destroy_node(link_type p);

		protected:
			size_type node_count; // 存储树的大小
			link_type header;     //根节点上方的头节点，一种实现方式
			Compare key_compare;  //比较方式，默认less<T>()

			//三个简便函数去取得header的成员
			link_type& root() const { return (link_type&)header->parent; }
			link_type& leftmost() const { return (link_type&)header->left; }
			link_type& rightmost() const { return (link_type&)header->right; }
			//以下六个函数用来方便取得节点X的成员
			static link_type& left(link_type x) { return (link_type&)(x->left); }
			static link_type& right(link_type x) { return (link_type&)(x->right); }
			static link_type& parent(link_type x) { return (link_type&)(x->parent); }
			static reference value(link_type x) { return x->value_field; }
			static const Key& key(link_type x) { return KeyOfValue()(value(x)); }
			static color_type& color(link_type x) { return (color_type&)(x->color); }
			//以下六个函数用来方便取得节点指针的成员
			static link_type& left(base_ptr x) { return (link_type&)(x->left); }
			static link_type& right(base_ptr x) { return (link_type&)(x->right); }
			static link_type& parent(base_ptr x) { return (link_type&)(x->parent); }
			static reference value(base_ptr x) { return ((link_type)x)->value_field; }
			static const Key& key(base_ptr x) { return KeyOfValue()(value(link_type(x))); }
			static color_type& color(base_ptr x) { return (color_type&)(link_type(x)->color); }
			//返回最大值和最小值的节点
			static link_type minimum(link_type x) {return (link_type)__rb_tree_node_base::minimum(x);}
			static link_type maximum(link_type x) {return (link_type)__rb_tree_node_base::maximum(x);}

		public:
			typedef __rb_tree_iterator<value_type, reference, pointer> iterator;
			typedef __rb_tree_iterator<value_type, const_reference, const_pointer>
				const_iterator;

	};
}
//imp/detail
#include"rb_tree_detail.h"

#endif // !_RB_TREE_H_

