#include<iostream>
#include"Allocator.h"
#include"Vector.h"
#include"TestVector.h"
#include"TestList.h"
#include<stack>
#include<vector>
#include"List.h"
#include"TestDeque.h"
int main() {
	STL::testList::testAll();
	STL::testVector::testAll();
	STL::testDeque::testAll();
	system("pause");
	return 0;
}