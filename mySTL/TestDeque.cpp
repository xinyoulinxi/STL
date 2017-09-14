#include"TestDeque.h"
#include<iostream>
namespace STL {
	namespace testDeque {

		void testAll() {
			testConstruct();
		}
		void testConstruct() {
			myDeque<int >deq;
			for (int i = 0; i < 700; i++) {
				deq.push_back(i);
			}


			//std::cout << deq.size() << std::endl;
			/*auto it = deq.begin();
			std::cout << *it <<std::endl;*/
		}

	}
}
