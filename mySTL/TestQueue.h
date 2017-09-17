#ifndef _TEST_DEQUE_H_
#define _TEST_DEQUE_H_
#include"Queue.h"
namespace STL{
	namespace testQueue {
		template<class T>
		using myQueue = queue<T>;
		typedef std::string Str;
		void testAll();
		void testConstruct();
		void testItemOp();
		void testItemGet();
	}
}
#endif // !_TEST_DEQUE_H_

