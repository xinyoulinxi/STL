#ifndef _RB_TREE_H_
#define _RB_TREE_H_
namespace STL {
	namespace detail {
		
		typedef bool __rb_tree_color_type;
		const __rb_tree_color_type __rb_tree_red = false;//ºìÉ«  0
		const __rb_tree_color_type __rb_tree_black = true;//ºÚÉ« 1

		struct __rb_tree_node_base {
			typedef __rb_tree_color_type color_type;
			typedef __rb_tree_node_base node_ptr;
			
		};
	}
}
#endif // !1

