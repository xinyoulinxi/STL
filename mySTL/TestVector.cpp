#include"TestVector.h"

namespace STL {
	namespace testVector {

		void testAll() {
			testPushBack();
			testInsert();
			testErase();
		}
		void testPushBack() {
			vector<int> vec;
			vec.push_back(1);

			assert(vec.size()==1);

			vec.push_back(2);
			vec.erase(vec.begin());
			assert(vec.size() == 1);
			
		}

		void testInsert() {
			vector<int> vec;
			vec.push_back(1);
			auto it = vec.begin();
		    vec.insert(it, 10, 5);

			/*	for (it=vec.begin(); it != vec.end(); ++it) {
			std::cout << *it << std::endl;
			}*/
			assert(vec.size() == 11);

			vector<int> vec1(10, 5);
			it = vec1.begin();
		
			auto size = vec1.size();
			assert(vec1.size() == 10);

			vector<int> vec3(10,3);
			int i = 0;
			for ( auto it =vec3.begin(); i < 10; i++) {
				 vec3.insert(it, i);
			}
			assert(vec3.size() == 20);

		}
		void testErase() {
			vector<int> vec;
			for (int i = 0; i < 10; i++) {
				vec.push_back(i);
			}
			int i = 1;
			for (auto it = vec.begin(); it != vec.begin();++i) {

				assert(vec.size() == i);
				it = vec.erase(vec.begin());
				if (i != 10) {
					assert(*it == i+1);
				}
			}
		}
	}
}