#include"TestDeque.h"
#include<iostream>
namespace STL {
	namespace testDeque {
		
		void testAll() {
			testConstruct();
		}
		void testConstruct() {
			myDeque<int >deq;
			deq.push_back(1);
			auto it = deq.begin();
			std::cout << *it <<std::endl;
		}

	}
}
