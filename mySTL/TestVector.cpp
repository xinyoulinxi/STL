#include"TestVector.h"

namespace STL {
	namespace testVector {

		void testAll() {
			test1();
			test2();
			test3();
		}
		void test1() {
			vector<int> vec;
			vec.push_back(1);

			std::cout << vec.size() << std::endl;
			assert(vec.size()==1);

			vec.push_back(2);
			vec.erase(vec.begin());
			assert(vec.size() == 2);
			
		}

		void test2() {
			vector<int> vec;
			vec.push_back(1);
			auto it = vec.begin();
		    vec.insert(it, 10, 5);
			/*	for (it=vec.begin(); it != vec.end(); ++it) {
			std::cout << *it << std::endl;
			}*/
			assert(vec.size() == 11);
			
		}
		void test3() {
			vector<int> vec;
		}
	}
}