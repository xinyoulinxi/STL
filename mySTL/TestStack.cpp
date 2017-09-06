#include"TestStack.h"
namespace STL {
	namespace testStack {
		static const Str testStr = "hello stack";
		void testAll(){
			testPopAndPush();
			testItemGet();
			testSize();
			testSwap();
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
			//string
			myStack<Str> stackStr1;
			for (int i = 0; i < 10; ++i) {
				stackStr1.push(testStr);
			}
			assert(stackStr1.size() == 10);
		}
		void testSwap() {
			//int
			myStack<int> stack1;
			myStack<int> stack2;
			stack1.push(1); stack1.push(5); stack1.push(7);
			stack2.push(2); stack2.push(3);
			assert(stack1.top() == 7 && stack2.top() == 3);
			stack1.swap(stack2);
			assert(stack2.top() == 7 && stack1.top() == 3);
			//string
			myStack<Str> stackStr1;
			myStack<Str> stackStr2;
			stackStr1.push("123"); stackStr1.push("34"); stackStr1.push("34");
			stackStr2.push("0"); stackStr2.push("11");
			assert(stackStr1.top() == "34" && stackStr2.top() == "22");
			stackStr1.swap(stackStr2);
			assert(stackStr2.top() == "34" && stackStr1.top() == "22");
		}
	}
}