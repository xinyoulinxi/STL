#include"TestVector.h"

namespace STL {
	namespace testVector {

		void testAll() {
			testPushBack();
			testInsert();
			testErase();
			testSize();
			testConstruct();

			testStdAndmySTL();
		}
		void testPushBack() {
			vector<int> vec;
			vec.push_back(1);

			assert(vec.size()==1);

			vec.push_back(2);
			vec.erase(vec.begin());
			assert(vec.size() == 1);
		}

		void testSize()
		{
			vector<int> vec;
			vec.push_back(1);
			assert(vec.size() == 1);
			vec.clear();
			assert(vec.size() == 0&&vec.empty());
			vec.resize(5);
			assert(vec.size() == 5 && vec[0] == int());

		}

		void testConstruct()
		{

			vector<int> vec1(5, 6);
			assert(vec1.size() == 5 && vec1[0] == 6);

			vector<int>vec2;
			assert(vec2.empty());

			vector<int> vec3(vec1.begin(), vec1.end());
			assert(vec3.size() == 5 && vec3[0] == 6);

			vector<int> vec4(vec1);
			assert(vec4.size() == 5 && vec4[0] == 6);

		}

		void testStdAndmySTL()
		{
			std::vector<std::string>
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

			vector<int> vec4;
			vec4.insert(vec4.begin(),vec.begin(), vec.end());
			assert(vec4.size() == 11);
			vec4.insert(vec4.begin(), 5, 1);
			assert(vec4[0] == 1);

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