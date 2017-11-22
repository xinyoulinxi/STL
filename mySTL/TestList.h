#include"List.h"
#include<list>
#include<string>
#include"Timer.h"
namespace STL {
	
	namespace testList {
	//#define TEST_ALL
	//测试所有的性能测试
		template<class T>
		using myList = STL::list<T>;
		
		template<class T>
		using stdList = std::list<T>;
		
		typedef std::string Str;

		void testAll();
		void testConstruct();
		void testInsert();
		void testErase();
		void testSplice();
		void testItemOp();
		void testUnique();
		void testRemove();
		void testClear();
		void testSize();
		void testGetItem();
		void testIterator();
		void testStdAndMySTL();
	}
}