#include"Deque.h"
#include<string>
namespace STL {
	namespace testDeque {
		template<class T>
		using myDeque = deque<T>;
		typedef std::string Str;

		void testAll();
		void testConstruct();
		void testItemOp();
		void testGetOp();
	}
}
