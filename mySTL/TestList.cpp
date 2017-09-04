#include"TestList.h"
namespace STL {
	namespace testList {
		static const Str testStr = "hello";
		void testAll()
		{
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
		void testConstruct()
		{
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
		void testInsert()
		{
		}
		void testErase()
		{
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