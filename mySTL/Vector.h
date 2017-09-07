#ifndef _VECTOR_H_
#define _VECTOR_H_

#include"Allocator.h"
#include"Iterator.h"
#include"Algorithm.h"
#include"UninitializedFunc.h"
#include<algorithm>
namespace STL {
	template <class T, class Alloc = allocator<T> >
	class vector {


	public:

		typedef T                       value_type;
		typedef value_type*             pointer;
		typedef value_type*             iterator;
		typedef value_type&             reference;
		typedef const value_type*       const_iterator;
		typedef const value_type&       const_reference;
		typedef size_t					size_type;
		typedef ptrdiff_t	            difference_type;
	private: 
		iterator start_;   //表示目前使用空间的头部
		iterator finish_;     //表示目前使用空间的尾部
		iterator end_of_storage_; //表示当前可用空间的尾部

		typedef Alloc data_Allocator;

	public:
		//构造函数，赋值构造函数，析构函数
		vector() :
			start_(0), finish_(0), end_of_storage_(0) {}
		vector(size_type n, const value_type& value);
		explicit vector(const size_type n);
		template<class InputIterator>
		vector(InputIterator first, InputIterator last);
		vector(const vector& v);
		vector(vector&& v);
		vector& operator = (const vector& v);
		vector& operator = (vector&& v);
		~vector();
		//比较操作
		bool operator ==(const vector& v)const;
		bool operator !=(const vector& v)const;

		
		//迭代器，位置相关
		iterator begin() { return (start_); }
		const_iterator begin() const { return (start_); }
		const_iterator end()const { return (finish_); }
		iterator end() { return (finish_); }
		const_iterator cbegin() { return (start_); }
		const_iterator cend() { return (start_); }

		//大小，容量
		size_type size()const { return  end() - begin(); }
		size_type capacity() const{ return end_of_storage_ - begin(); }
		bool empty()const { return begin() == end(); }
		void resize(size_t n,value_type value=value_type());
		void reserve(size_t n);
		void shrink_to_fit();//删除未使用的容量
		//元素访问
		reference operator[](const difference_type i) { return *(begin() + i); }
		const_reference operator[](const difference_type i)const { return *(cbegin() + i); }
		reference front() { return *begin(); }//第一个元素
		reference back() { return *(end() - 1); }//最后一个元素
		reference operator[](size_type i) { return *(begin() + i); }
		pointer data() { return start_; }
		reference at(size_type pos);
		const_reference at(size_type pos)const;

		//容器内容的修改操作函数
		void clear();
//		void copy(iterator start, iterator new_start);
//		void swap(vector& v);

		void pop_back();
		void insert(iterator position, const size_type& n, const value_type& val);
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		iterator insert(iterator position, const value_type& value);
		void push_back(const value_type & value);//末尾添加
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);

		//空间配置器相关的操作函数
		data_Allocator get_allocator() { return data_Allocator; }
	private:
		template<class InputIterator>
		void __insert(iterator position, InputIterator first, InputIterator last, std::false_type);
		void __insert(iterator position,size_type n, const value_type& value, std::true_type);

		void deallocate();
		void fill_initialize(size_t n, const value_type& value);
		void allocateAndFillN(size_type n, const T& x);
		template<class InputIterator>
		void allocateAndCopy(InputIterator first, InputIterator last);
		template<class InputIterator>
		void reallocateAndCopy(iterator position, InputIterator first, InputIterator last);
		void reallocateAndFillN(iterator position, const size_type& n, const value_type& value);

		size_type getNewCapacitySize(size_type n)const;

		template<class InputIterator>
		void __vector(InputIterator first, InputIterator last, std::false_type);
		template<class Integer>
		void __vector(Integer n, const value_type& value, std::true_type);
		
		//         =。=
	public:   
		template<class T, class Alloc>
		friend bool operator == (const vector<T, Alloc>& v1, const vector<T, Alloc>& v2);
		template<class T, class Alloc>
		friend bool operator != (const vector<T, Alloc>& v1, const vector<T, Alloc>& v2);


	};

}
//实现
#include"Vector_detail.h"
#endif