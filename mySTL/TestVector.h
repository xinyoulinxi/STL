#pragma once
#include"Vector.h"
#include<cassert>
#include<iostream>
#include<vector>
#include<string>
namespace STL {
	namespace testVector {
		template<class T>
		using vector = STL::vector<T>;

		void testAll();
		void testInsert();
		void testErase();
		void testPushBack();
		void testSize();
		void testConstruct();
		void testStdAndmySTL();
	}
}