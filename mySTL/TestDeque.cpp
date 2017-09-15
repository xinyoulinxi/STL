#include"TestDeque.h"
#include<iostream>
namespace STL {
	namespace testDeque {

		void testAll() {
			testConstruct();
			testItemOp();
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

		void testItemOp()
		{
			myDeque<int >deq;
			for (int i = 0; i < 100; i++) {
				deq.push_back(i);
			}
			for (int i = 0; i < 99; i++) {
				deq.pop_back();
			}
			for (int i = 0; i < 100; i++) {
				deq.push_front(i);
			}
			for (int i = 0; i < 99; i++) {
				deq.pop_front();
			}
		}

	}
}
