#include"TestVector.h"

namespace STL {
	namespace testVector {
		static const std::string str = "hello vector";
		void testAll() {
			testPushBack();
			testInsert();
			testErase();
			testSize();
			testConstruct();

			testStdAndmySTL();
		}
		void testPushBack() {
			//int
			myVector<int> vec;
			vec.push_back(1);

			assert(vec.size()==1);

			vec.push_back(2);
			vec.erase(vec.begin());
			assert(vec.size() == 1);

			//string
			myVector<std::string> vecS;
			vecS.push_back(str);
			assert(vecS[0] == str);
			vecS.push_back(std::string(str));
			assert(vecS[0] == str);
			for (int i = 0; i < 10; i++) {
				vecS.push_back(str);
			}
		}

		void testSize()
		{
			//int
			myVector<int> vec;
			vec.push_back(1);
			assert(vec.size() == 1);
			vec.clear();
			assert(vec.size() == 0&&vec.empty());
			vec.resize(5);
			assert(vec.size() == 5 && vec[0] == int());
			vec.clear();
			vec.shrink_to_fit();
			assert(vec.capacity() == 0);
			//string
			myVector<std::string> vecS;
			vecS.push_back(str);
			assert(vecS.size() == 1);
			vecS.clear();
			assert(vecS.size() == 0 && vecS.empty());
			vecS.resize(5);
			assert(vecS.size() == 5 && vecS[0] == std::string());
			vecS.clear();
			vecS.shrink_to_fit();
			assert(vecS.capacity() == 0);

		}

		void testConstruct()
		{
			//int
			myVector<int> vec1(5, 6);
			assert(vec1.size() == 5 && vec1[0] == 6);

			myVector<int>vec2;
			assert(vec2.empty());

			myVector<int> vec3(vec1.begin(), vec1.end());
			assert(vec3.size() == 5 && vec3[0] == 6);

			myVector<int> vec4(vec1);
			assert(vec4.size() == 5 && vec4[0] == 6);

			//string
			myVector<std::string> vecS1(5, str);
			assert(vecS1.size() == 5 && vecS1[0] == str);

			myVector<std::string>vecS2;
			assert(vecS2.empty());

			myVector<std::string> vecS3(vecS1.begin(), vecS1.end());
			assert(vecS3.size() == 5 && vecS3[0] == str);

			myVector<std::string> vecS4(vecS1);
			assert(vecS4.size() == 5 && vecS4[0] == str);

		}

		void testStdAndmySTL()
		{
			//int
			myVector<int> myV;
			stdVector<int> stdV;
			for (int i = 0; i < 100000; i++) {
				
			}
		}

		void testInsert() {
			//int
			myVector<int> vec;
			vec.push_back(1);
			auto it = vec.begin();
		    vec.insert(it, 10, 5);

			/*	for (it=vec.begin(); it != vec.end(); ++it) {
			std::cout << *it << std::endl;
			}*/
			assert(vec.size() == 11);

			myVector<int> vec1(10, 5);
			it = vec1.begin();
		
			assert(vec1.size() == 10);

			myVector<int> vec3(10,3);
			int i = 0;
			for ( auto it =vec3.begin(); i < 10; i++) {
				 it=vec3.insert(it, i);
			}
			assert(vec3.size() == 20);

			myVector<int> vec4;
			vec4.insert(vec4.begin(),vec.begin(), vec.end());
			assert(vec4.size() == 11);
			vec4.insert(vec4.begin(), 5, 1);
			assert(vec4[0] == 1);

			//string
			myVector<std::string> vecS;
			vecS.push_back(str);
			auto itS = vecS.begin();
			vecS.insert(itS, 10, str);
			assert(vecS.size() == 11);

			myVector<std::string> vecS1(10, str);
			itS = vecS1.begin();

			assert(vecS1.size() == 10);

			myVector<std::string> vecS3(10, str);
			i = 0;
			for (auto itS = vecS3.begin(); i < 10; i++) {
				itS=vecS3.insert(itS, str);
			}
			assert(vecS3.size() == 20);

			myVector<std::string> vecS4;
			vecS4.insert(vecS4.begin(), vecS.begin(), vecS.end());
			assert(vecS4.size() == 11);
			vecS4.insert(vecS4.begin(), 5, str);
			assert(vecS4[0] == str);

		}
		void testErase() {
			//int
			myVector<int> vec;
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
			//string
			myVector<std::string> vecS;
			for (int i = 0; i < 10; i++) {
				vecS.push_back(str);
			}
			 i = 1;
			for (auto it = vecS.begin(); it != vecS.begin(); ++i) {

				assert(vecS.size() == i);
				it = vecS.erase(vecS.begin());
				if (i != 10) {
					assert(*it == str);
				}
			}
		}
	}
}