#pragma once
#include"Vector.h"
#include<cassert>
#include<iostream>
namespace STL {
	namespace testVector {
		template<class T>
		using vector = STL::vector<T>;

		void testAll();
		void test1();
		void test2();
		void test3();
	}
}