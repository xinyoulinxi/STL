#include"TestDeque.h"
#include<iostream>
namespace STL {
	namespace testDeque {
		const static Str testStr = "hello deque";
		void testAll() {
			testConstruct();
			testItemOp();
			testGetOp();
		}
		void testConstruct() {
			//int
			myDeque<int >deq;
			assert(deq.empty());
			for (int i = 0; i <10; i++) {
				deq.push_back(i);
			}
			assert(*deq.begin() == 0);

			myDeque<int >deq1(100,5);
			assert(deq1.size() == 100 );

			myDeque<int >deq2(deq.begin(), deq.end());
			assert(*deq2.begin() == 0&&deq2.size()==10);

			//string
			myDeque<Str >deqStr;
			assert(deqStr.empty());
			for (int i = 0; i <10; i++) {
				deqStr.push_back(testStr);
			}
			assert(*deqStr.begin() == testStr);

			myDeque<Str >deqStr1(100, testStr);
			assert(deqStr1.size() == 100);

			myDeque<Str >deqStr2(deqStr.begin(), deqStr.end());
			assert(*deqStr2.begin() == testStr && deqStr2.size() == 10);
		}

		void testItemOp(){
			//int
			myDeque<int >deq;
			for (int i = 0; i < 10; i++) {
				deq.push_back(i);
			}
			assert(deq.size() == 10);
			assert(*deq.begin() == 0);
			for (int i = 0; i < 10; i++) {
				deq.pop_front();
			}
			assert(deq.empty());

			myDeque<int >deq1;
			for (int i = 0; i < 10; i++) {
				deq1.push_front(i);
			}
			assert(deq1.size() == 10);
			assert(*deq1.begin() == 9);
			for (int i = 0; i < 10; i++) {
				deq1.pop_back();
			}
			assert(deq1.empty());

			//string
			myDeque<Str >deqStr;
			for (int i = 0; i < 10; i++) {
				deqStr.push_back(testStr);
			}
			assert(deqStr.size() == 10);
			assert(*deqStr.begin() == testStr);
			for (int i = 0; i < 10; i++) {
				deqStr.pop_front();
			}
			assert(deqStr.empty());

			myDeque<Str >deqStr1;
			for (int i = 0; i < 10; i++) {
				deqStr1.push_front(testStr);
			}
			assert(deqStr1.size() == 10);
			assert(*deqStr1.begin() == testStr);
			for (int i = 0; i < 10; i++) {
				deqStr1.pop_back();
			}
			assert(deqStr1.empty());
		}
		myDeque<int> getDeque() {
			return myDeque<int>();
		}
		void testGetOp(){
			deque<int> d(getDeque());
			//int 
			myDeque<int >deq;
			deq.push_back(1);
			deq.push_back(2);
			assert(deq.front() == 1);
			assert(deq.back() == 2);
			assert(deq.back() == deq[1]);
			assert(deq.size() == 2);
			//string
			myDeque<Str >deqStr;
			deqStr.push_back(testStr);
			deqStr.push_back(testStr);
			assert(deqStr.front() == testStr);
			assert(deqStr.back() == testStr);
			assert(deqStr.back() == deqStr[1]);
			assert(deqStr.size() == 2);
		}
	}
}
