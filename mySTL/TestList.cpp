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
			
		}
		void testSplice()
		{
		}
		void testItemOp()
		{
		}
		void testUnique()
		{
		}
		void testRemove()
		{
		}
		void testClear()
		{
		}
		void testSize()
		{
		}
		void testGetItem()
		{
		}
		void testIterator()
		{
		}
	}
}