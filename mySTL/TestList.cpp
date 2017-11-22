#include"TestList.h"
namespace STL {
	namespace testList {
		static const Str testStr = "hello list";
		
		void testAll(){
			testConstruct();
			testInsert();
			testErase();
			testSplice();
			testItemOp();
			testUnique();
			testRemove();
			testClear();
			testSize();
			testGetItem();
			testIterator();
			testStdAndMySTL();
		}
		void testConstruct(){
			//int
			myList<int> lis1;
			
			myList<int> lis2(5, 1);
			assert(lis2.size() == 5);
			
			myList<int> lis3(lis2.begin(), lis2.end());
			assert(lis3.size() == 5);

			myList<int> lis4(lis2);
			assert(lis4.size() == 5);
			
			myList<int> lis5 = lis4;
			assert(lis4.size() == 5);

			//string
			myList<Str> lisStr1;

			myList<Str> lisStr2(5, testStr);
			assert(lisStr2.size() == 5);

			myList<Str> lisStr3(lisStr2.begin(), lisStr2.end());
			assert(lisStr3.size() == 5);

			myList<Str> lisStr4(lisStr2);
			assert(lisStr4.size() == 5);

			myList<Str> lisStr5 = lisStr4;
			assert(lisStr4.size() == 5);

		}
		void testInsert(){
			//int
			myList<int> lis1;
			lis1.insert(lis1.begin(), 1);
			assert(*(lis1.begin()) == 1);

			myList<int> lis2;
			lis2.insert(lis2.begin(), lis1.begin(), lis1.end());
			assert(lis1 == lis2);
			
			myList<int> lis3;
			lis3.insert(lis3.begin(), 5, 10);
			assert(lis3.size() == 5 && *(lis3.begin()) == 10);

			
			//string
			myList<Str> lisStr1;
			lisStr1.insert(lisStr1.begin(), testStr);
			assert(*(lisStr1.begin()) == testStr);

			myList<Str> lisStr2;
			lisStr2.insert(lisStr2.begin(), lisStr1.begin(), lisStr1.end());
			assert(lisStr1 == lisStr2);

			myList<Str> lisStr3;
			lisStr3.insert(lisStr3.begin(), 5, testStr);
			assert(lisStr3.size() == 5 && *(lisStr3.begin()) == testStr);

		}
		void testErase(){
			//int 
			myList<int> lis1;
			for (int i = 0; i < 10; i++) {
				lis1.push_back(i);
			}
			lis1.erase(lis1.begin());
			assert(lis1.size() == 9&&*lis1.begin()==1);

			myList<int> lis2;
			for (int i = 0; i < 10; i++) {
				lis2.push_back(i);
			}
			lis2.erase(lis2.begin(), lis2.end());
			assert(lis2.size() == 0);
			//string
			myList<Str> lisStr1;
			for (int i = 0; i < 10; i++) {
				lisStr1.push_back(testStr);
			}
			lisStr1.erase(lisStr1.begin());
			assert(lisStr1.size() == 9 && *lisStr1.begin() == testStr);

			myList<Str> lisStr2;
			for (int i = 0; i < 10; i++) {
				lisStr2.push_back(testStr);
			}
			lisStr2.erase(lisStr2.begin(), lisStr2.end());
			assert(lisStr2.size() == 0);
			
		}
		void testSplice()
		{
			myList<int >lis1(5, 1);
			myList<int >lis2(5, 3);

			lis1.splice(lis1.begin(),lis2);
			assert(lis1.size() == 10 && *lis1.begin() == 3);
			assert(lis2.empty());
			
			myList<int >lis3(5, 3);
			//lis3.splice(lis3.begin(), lis1, lis1.begin());
			//assert(*lis3.begin() == 3 && lis3.size() == 6);



		}
		bool isEqualeInt(const int& a, const int& b) {
			return a == b;

		}
		bool isEqualeString(const Str& a, const Str& b) {
			return a == b;
		}
		void testItemOp(){
			//int
			myList<int> lis1;
			lis1.push_back(1);
			assert(*lis1.begin() == 1);
			lis1.push_front(2);
			assert(*lis1.begin() == 2);
			lis1.pop_back();
			auto itLast = --(lis1.end());
			assert(*itLast == 2);
			lis1.push_back(1);
			lis1.pop_front();
			auto itBegin = lis1.begin();
			assert(*itBegin == 1);// 1
			for (int i = 0; i < 10; i++) {
				lis1.push_back(i);
				lis1.push_front(i);
			}
			assert(*lis1.begin() == 9);
			for (int i = 0; i < 10; i++) {
				lis1.pop_back();
				lis1.pop_front();
			}//1
			assert(*lis1.begin() == 1);
			//string
			myList<Str> lisStr1;
			lisStr1.push_back(testStr);
			assert(*lisStr1.begin() == testStr);
			lisStr1.push_front(testStr);
			assert(*lisStr1.begin() == testStr);
			lisStr1.pop_back();
			auto itLastStr = --(lisStr1.end());
			assert(*itLastStr == testStr);
			lisStr1.push_back(testStr);
			lisStr1.pop_front();
			auto itBeginStr = lisStr1.begin();
			assert(*itBeginStr == testStr);// 1
			for (int i = 0; i < 10; i++) {
				lisStr1.push_back(testStr);
				lisStr1.push_front(testStr);
			}
			assert(*lisStr1.begin() == testStr);
			for (int i = 0; i < 10; i++) {
				lisStr1.pop_back();
				lisStr1.pop_front();
			}//1
			assert(*lisStr1.begin() == testStr);
		}
		void testUnique(){
			//int 
			myList<int> lis1;
			for (int i = 0; i < 10; i++) {
				lis1.push_back(i);
				lis1.push_back(i);
			}
			assert(lis1.size() == 20);
			lis1.unique();
			assert(lis1.size() == 10);
			lis1.clear();
			for (int i = 0; i < 10; i++) {
				lis1.push_back(i);
				lis1.push_back(i);
			}
			assert(lis1.size() == 20);
			lis1.unique(isEqualeInt);
			assert(lis1.size() == 10);
			//string
			myList<Str> lisStr1;
			for (int i = 0; i < 10; i++) {
				lisStr1.push_back(testStr);
				lisStr1.push_back(testStr);
			}
			assert(lisStr1.size() == 20);
			lisStr1.unique();
			assert(lisStr1.size() == 1);
			lisStr1.clear();
			for (int i = 0; i < 10; i++) {
				lisStr1.push_back(testStr);
				lisStr1.push_back(testStr);
			}
			assert(lisStr1.size() == 20);
			lisStr1.unique(isEqualeString);
			assert(lisStr1.size() == 1);
		}
		//testRemove() testfunction
		bool isRemoveInt(const int& val) {
			if (val > 0) {
				return true;
			}
			return false;
		}
		bool isRemoveStr(const Str& val) {
			if (val[0] =='h') {
				return true;
			}
			return false;
		}
		void testRemove()
		{
			//int 
			myList<int> lis1(5,1);
			lis1.remove(1);
			assert(lis1.empty());

			myList<int> lis2(5, 1);
			lis2.push_back(-7);
			lis2.remove_if(isRemoveInt);
			assert(lis2.size()==1);

			//string
			myList<Str> lisStr1(5, testStr);
			lisStr1.remove(testStr);
			assert(lis1.empty());

			myList<Str> lisStr2(5, testStr);
			lisStr2.push_back("metoo");
			lisStr2.remove_if(isRemoveStr);
			assert(lisStr2.size() == 1);
		}
		void testClear(){
			//int 
			myList<int> lis1;
			for (int i = 0; i < 10; i++) {
				lis1.push_back(i);
			}
			assert(lis1.size() == 10);
			lis1.clear();
			assert(lis1.empty());
			//string
			myList<Str> lisStr1;
			for (int i = 0; i < 10; i++) {
				lisStr1.push_back(testStr);
			}
			assert(lisStr1.size() == 10);
			lisStr1.clear();
			assert(lisStr1.empty());
		}
		void testSize()
		{
			//int 
			myList<int> lis1;
			for (int i = 0; i < 10; i++) {
				lis1.push_back(i);
			}
			assert(lis1.size() == 10);
			lis1.clear();
			assert(lis1.size()==0);
			//string
			myList<Str> lisStr1;
			for (int i = 0; i < 10; i++) {
				lisStr1.push_back(testStr);
			}
			assert(lisStr1.size() == 10);
			lisStr1.clear();
			assert(lisStr1.size() == 0);
		}
		void testGetItem()
		{
			//int 
			int i = 0;
			myList<int> lis1;
			for (i = 0; i < 10; i++) {
				lis1.push_back(i);
			}
			assert(lis1.back() == 9);
			assert(lis1.front()== 0);
			//string
			myList<Str> lisStr1;
			for (i = 0; i < 10; i++) {
				lisStr1.push_back(testStr);
			}
			assert(lisStr1.back() == testStr);
			assert(lisStr1.front() == testStr);
		}
		void testIterator(){
			//int 
			int i = 0;
			myList<int> lis1;
			for (i = 0; i < 10; i++) {
				lis1.push_back(i);
			}
			i = 0;
			for (auto it = lis1.begin(); it != lis1.end(); ++it) {
				assert(*it == i++);
			}
			i = 9;
			for (auto it =lis1.end(); it != lis1.end(); ) {
				--it;
				assert(*it == i--);
			}
			//string
			myList<Str> lisStr1;
			for (i = 0; i < 10; i++) {
				lisStr1.push_back(testStr);
			}

			for (auto it = lisStr1.begin(); it != lisStr1.end(); ++it) {
				assert(*it == testStr);
			}
			for (auto it = lisStr1.end(); it != lisStr1.end();) {
				--it;
				assert(*it ==testStr);
			}
		}
		void testStdAndMySTL(){
#ifdef TEST_ALL
			

     //**********************************进行简单类型的std和STL的性能测试*********************************
		//1、以下是对list的普通类型的插入操作进行性能测试(同时也是对push_back()和push_front()的测试)
			//10^5
			{
				
				stdList<int> stdIntLis;
				myList<int> myIntLis;

				//普通类型  10^5  std
				Timer::start();
				for (int i = 0; i < 100000; ++i) {
					stdIntLis.insert(stdIntLis.begin(), i);
				}
				Timer::finish();
				Timer::PrintUsedTimeOnStream(std::cout);

				//普通类型  10^5  STL
				Timer::start();
				for (int i = 0; i < 100000; ++i) {
					myIntLis.insert(myIntLis.begin(), i);
				}
				Timer::finish();
				Timer::PrintUsedTimeOnStream(std::cout);
				/*
				100000数量级情况下
				两者对比如下：
				std::list: 4 ms
				STL::List: 1 ms
				*/
			}

			//10^6
			{

				stdList<int> stdIntLis;
				myList<int> myIntLis;

				//普通类型  10^6  std
				Timer::start();
				for (int i = 0; i < 1000000; ++i) {
					stdIntLis.insert(stdIntLis.begin(), i);
				}
				Timer::finish();
				Timer::PrintUsedTimeOnStream(std::cout);

				//普通类型  10^6  STL
				Timer::start();
				for (int i = 0; i < 1000000; ++i) {
					myIntLis.insert(myIntLis.begin(), i);
				}
				Timer::finish();
				Timer::PrintUsedTimeOnStream(std::cout);
				/*
				100000数量级情况下
				两者对比如下：
				std::list: 59 ms
				STL::List: 12 ms
				*/
			}

			//10^7
			{

				stdList<int> stdIntLis;
				myList<int> myIntLis;

				//普通类型  10^7  std
				Timer::start();
				for (int i = 0; i < 10000000; ++i) {
					stdIntLis.insert(stdIntLis.begin(), i);
				}
				Timer::finish();
				Timer::PrintUsedTimeOnStream(std::cout);

				//普通类型  10^7  STL
				Timer::start();
				for (int i = 0; i < 10000000; ++i) {
					myIntLis.insert(myIntLis.begin(), i);
				}
				Timer::finish();
				Timer::PrintUsedTimeOnStream(std::cout);
				/*
				100000数量级情况下
				两者对比如下：
				std::list: 546 ms
				STL::List: 132 ms
				*/
			}

		//2、以下是对list的复杂类型的插入操作进行性能测试(同时也是对push_back()和push_front()的测试)
			//10^5
			{

				stdList<Str> stdStrLis;
				myList<Str> myStrLis;

				//普通类型  10^5  std
				Timer::start();
				for (int i = 0; i < 100000; ++i) {
					stdStrLis.insert(stdStrLis.begin(), testStr);
				}
				Timer::finish();
				Timer::PrintUsedTimeOnStream(std::cout);

				//普通类型  10^5  STL
				Timer::start();
				for (int i = 0; i < 100000; ++i) {
					myStrLis.insert(myStrLis.begin(), testStr);
				}
				Timer::finish();
				Timer::PrintUsedTimeOnStream(std::cout);
				/*
				100000数量级情况下
				两者对比如下：
				std::list: 9 ms
				STL::List: 4 ms
				*/
			}

			//10^6
			{

				stdList<Str> stdStrLis;
				myList<Str> myStrLis;

				//普通类型  10^6  std
				Timer::start();
				for (int i = 0; i < 1000000; ++i) {
					stdStrLis.insert(stdStrLis.begin(), testStr);
				}
				Timer::finish();
				Timer::PrintUsedTimeOnStream(std::cout);

				//普通类型  10^6  STL
				Timer::start();
				for (int i = 0; i < 1000000; ++i) {
					myStrLis.insert(myStrLis.begin(), testStr);
				}
				Timer::finish();
				Timer::PrintUsedTimeOnStream(std::cout);
				/*
				1000000数量级情况下
				两者对比如下：
				std::list: 77 ms
				STL::List: 37 ms
				*/
			}

			//10^7
			{

				stdList<Str> stdStrLis;
				myList<Str> myStrLis;

				//普通类型  10^7  std
				Timer::start();
				for (int i = 0; i < 10000000; ++i) {
					stdStrLis.insert(stdStrLis.begin(), testStr);
				}
				Timer::finish();
				Timer::PrintUsedTimeOnStream(std::cout);

				//普通类型  10^7  STL
				Timer::start();
				for (int i = 0; i < 10000000; ++i) {
					myStrLis.insert(myStrLis.begin(), testStr);
				}
				Timer::finish();
				Timer::PrintUsedTimeOnStream(std::cout);
				/*
				10000000数量级情况下
				两者对比如下：
				std::list: 744 ms
				STL::List: 296 ms
				*/
			}
#endif //TEST_ALL
		}
	}
}