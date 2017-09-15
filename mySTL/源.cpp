#include<iostream>
#include"Allocator.h"
#include"Vector.h"
#include"TestVector.h"
#include"TestList.h"
#include<stack>
#include<vector>
#include<deque>
#include"List.h"
#include"TestDeque.h"
int main() {
	std::deque<int> q;
	STL::testList::testAll();
	STL::testVector::testAll();
	STL::testDeque::testAll();
	system("pause");
	return 0;
}