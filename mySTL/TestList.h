#include"List.h"
#include<list>
#include<string>
namespace STL {
	namespace testList {
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
		
	}
}