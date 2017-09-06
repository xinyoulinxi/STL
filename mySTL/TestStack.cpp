#include"TestStack.h"
namespace STL {
	namespace testStack {
		static const Str testStr = "hello stack";
		void testAll(){
			testPopAndPush();
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
		void testItemGet()
		{
			//int
			myStack<int> stack1;
			stack1.push(1);
			assert(stack1.top() == 1);
			stack1.top() = 5;
			assert(stack1.top() == 5);
			//string
			myStack<Str> stackStr1;
			stackStr1.push(testStr);
			assert(stackStr1.top() == testStr);
			stackStr1.top() = "me";
			assert(stackStr1.top() == "me");
		}
		void testSize()
		{
			//int
			myStack<int> stack1;
			for (int i = 0; i < 10; ++i) {
				stack1.push(i);
			}
			assert(stack1.size() == 10);
		}
	}
}