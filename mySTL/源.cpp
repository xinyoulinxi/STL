#include<iostream>
#include"Allocator.h"
#include"Vector.h"
#include"TestVector.h"
#include<stack>
#include<vector>
#include"List.h"
int main() {

	STL::list<int> lis;
	lis.push_back(1);
	lis.push_back(1);
	lis.push_front(2);
	std::cout << lis.size() << std::endl;
	lis.unique();
	std::cout << lis.size() << std::endl;
	STL::testVector::testAll();
	system("pause");
	return 0;
}