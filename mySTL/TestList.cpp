#include"TestList.h"
namespace STL {
	namespace testList {
		static const Str testStr = "hello";
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
			
		}
		void testIterator()
		{
		}
	}
}