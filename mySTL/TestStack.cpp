#include"TestStack.h"
namespace STL {
	namespace testStack {
		static const Str testStr = "hello stack";
		void testAll(){
			testPopAndPush();
			testConstruct();
			testItemGet();
			testSize();
		}
		void testPopAndPush(){
			//int
			myStack<int> stack1;
			stack1.push(1);
			assert(stack1.top() == 1);
			stack1.pop();
			assert(stack1.empty());
			//string
			myStack<Str> stackStr1;
			stackStr1.push(testStr);
			assert(stackStr1.top() == testStr);
			stackStr1.pop();
			assert(stack1.empty());
		}
		void testConstruct()
		{

		}
		void testItemGet()
		{
		}
		void testSize()
		{
		}
	}
}