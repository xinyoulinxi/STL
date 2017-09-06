#pragma once
#include"Stack.h"
#include<string>
namespace STL{
	namespace testStack {
		template<class T>
		using myStack = STL::stack<T>;

		typedef std::string Str ;

		void testAll();
		void testPopAndPush();
		void testConstruct();
		void testItemGet();
		void testSize();

	}
}