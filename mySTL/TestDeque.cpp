#include"TestDeque.h"
#include<iostream>
namespace STL {
	namespace testDeque {
		
		void testAll() {
			testConstruct();
		}
		void testConstruct() {
			myDeque<int >deq;
			for (int i = 0; i < 100; i++) {
				deq.push_back(i);
			}
			
			auto it = deq.begin();
			std::cout << *it <<std::endl;
		}

	}
}
