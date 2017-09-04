#include"TestList.h"
namespace STL {
	namespace testList {
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
			myList<int> lis1;
			
			myList<int> lis2(5, 1);
			assert(lis2.size() == 5);
			
			myList<int> lis3(lis2.begin(), lis2.end());
			assert(lis3.size() == 5);

			myList<int> lis4(lis2);
			assert(lis4.size() == 5);
			
			myList<int> lis5 = lis4;
			assert(lis4.size() == 5);
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