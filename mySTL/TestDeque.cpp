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
			for (int i = 0; i <2; i++) {
				deq.push_back(i);
			}
			myDeque<int >deq1(100,5);
			std::cout << deq1.size() << std::endl;
			std::cout << deq.size() << std::endl;
			myDeque<int >deq2(deq.begin(), deq.end());
			//std::cout << deq.size() << std::endl;
			/*auto it = deq.begin();
			std::cout << *it <<std::endl;*/
		}

		void testItemOp()
		{
			myDeque<int >deq;
			for (int i = 0; i < 1000; i++) {
				deq.push_back(i);
			}
			for (int i = 0; i < 1000; i++) {
				deq.pop_front();
			}
		}

	}
}
