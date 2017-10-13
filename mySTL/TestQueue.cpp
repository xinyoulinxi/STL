#include"Queue.h"
#include "TestQueue.h"
#include<string>
namespace STL {
	namespace testQueue {
		static Str testStr = "hello queue";
		void testAll(){
			testConstruct();
			testItemOp();
			testItemGet();
		}
		void testConstruct(){
			myQueue<int> que;

			
		}
		void testItemOp(){
			//int 
			myQueue<int> que;
			que.push(1);
			assert(que.front() == 1);
			assert(que.size() == 1);
			que.pop();
			assert(que.size() == 0);
			assert(que.empty());
			//string
			myQueue<Str> queStr;
			queStr.push(testStr);
			assert(queStr.front() == testStr);
			assert(queStr.size() == 1);
			queStr.pop();
			assert(queStr.size() == 0);
			assert(queStr.empty());
		}
		void testItemGet(){
			//int 
			myQueue<int> que;
			que.push(1);
			assert(que.front() == 1);
			//string
			myQueue<Str> queStr;
			queStr.push(testStr);
			assert(queStr.front() == testStr);
		}
	}
}