#include<iostream>
#include"Allocator.h"
#include"Vector.h"
#include"TestVector.h"
#include<stack>
#include<vector>
#include"List.h"
int main() {

	STL::list<int> lis1;
	for (int i = 1; i <= 5; ++i) {
		lis1.push_back(i);//1,2,3,4,5
	}
	STL::list<int> lis2;
	for (int i = 3; i >=0; --i) {
		lis2.push_back(i);//3,2,1,0
	}
	for (auto it = lis1.begin(); it != lis1.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	for (auto it = lis2.begin(); it != lis2.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	lis1.splice(lis1.begin(), lis2);
	
	for (auto it = lis1.begin(); it != lis1.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}