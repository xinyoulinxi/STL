#include"TestVector.h"
#include"Timer.h"
namespace STL {
	namespace testVector {
		static const std::string testStr = "hello vector";
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
			vecS.push_back(testStr);
			assert(vecS[0] == testStr);
			vecS.push_back(std::string(testStr));
			assert(vecS[0] == testStr);
			for (int i = 0; i < 10; i++) {
				vecS.push_back(testStr);
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
			vecS.push_back(testStr);
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
			myVector<std::string> vecS1(5, testStr);
			assert(vecS1.size() == 5 && vecS1[0] == testStr);

			myVector<std::string>vecS2;
			assert(vecS2.empty());

			myVector<std::string> vecS3(vecS1.begin(), vecS1.end());
			assert(vecS3.size() == 5 && vecS3[0] == testStr);

			myVector<std::string> vecS4(vecS1);
			assert(vecS4.size() == 5 && vecS4[0] == testStr);

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
			vecS.push_back(testStr);
			auto itS = vecS.begin();
			vecS.insert(itS, 10, testStr);
			assert(vecS.size() == 11);

			myVector<std::string> vecS1(10, testStr);
			itS = vecS1.begin();

			assert(vecS1.size() == 10);

			myVector<std::string> vecS3(10, testStr);
			i = 0;
			for (auto itS = vecS3.begin(); i < 10; i++) {
				itS=vecS3.insert(itS, testStr);
			}
			assert(vecS3.size() == 20);

			myVector<std::string> vecS4;
			vecS4.insert(vecS4.begin(), vecS.begin(), vecS.end());
			assert(vecS4.size() == 11);
			vecS4.insert(vecS4.begin(), 5, testStr);
			assert(vecS4[0] == testStr);

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
				vecS.push_back(testStr);
			}
			 i = 1;
			for (auto it = vecS.begin(); it != vecS.begin(); ++i) {

				assert(vecS.size() == i);
				it = vecS.erase(vecS.begin());
				if (i != 10) {
					assert(*it == testStr);
				}
			}
		}
		void testStdAndmySTL()
		{
			//以下所有测试都是在release模式下进行
			// *************************以下是对简单类型的vector的push_back函数性能测试****************************

#ifdef TEST_ALL


			//10^7
			{
				// myVector  10^7
				STL::Timer::start();
				STL::vector<int> myIntVec;
				for (int i = 0; i < 10000000; ++i) {
					myIntVec.push_back(i);
				}
				STL::Timer::finish();
				STL::Timer::PrintUsedTimeOnStream(std::cout);

				//std::vector 10^7
				STL::Timer::start();
				std::vector<int> stdIntVec;
				for (int i = 0; i < 10000000; ++i) {
					stdIntVec.push_back(i);
				}
				STL::Timer::finish();
				STL::Timer::PrintUsedTimeOnStream(std::cout);
				/*
				10000000数量级情况下
				两者对比如下：
				myVector:    120 ms
				std::vector: 137 ms
				*/
			}

			//10^6
			{
				//myVector  10^6
				STL::Timer::start();
				STL::vector<int> myIntVec;
				for (int i = 0; i < 1000000; ++i) {
					myIntVec.push_back(i);
				}
				STL::Timer::finish();
				STL::Timer::PrintUsedTimeOnStream(std::cout);

				//std::vector 10^6
				STL::Timer::start();
				std::vector<int> stdIntVec;
				for (int i = 0; i < 1000000; ++i) {
					stdIntVec.push_back(i);
				}
				STL::Timer::finish();
				STL::Timer::PrintUsedTimeOnStream(std::cout);
				/*
				两者对比如下：
				myVector:    11 ms
				std::vector: 12 ms
				*/
			}

			//10^5
			{
				//myVector  10^5
				STL::Timer::start();
				STL::vector<int> myIntVec;
				for (int i = 0; i < 100000; ++i) {
					myIntVec.push_back(i);
				}
				STL::Timer::finish();
				STL::Timer::PrintUsedTimeOnStream(std::cout);

				//std::vector 10^5
				STL::Timer::start();
				std::vector<int> stdIntVec;
				for (int i = 0; i < 100000; ++i) {
					stdIntVec.push_back(i);
				}
				STL::Timer::finish();
				STL::Timer::PrintUsedTimeOnStream(std::cout);
				/*
				两者对比如下：
				myVector:    1 ms
				std::vector: 1 ms
				*/
			}


			// *************************以下是对复杂类型的vector的insert函数性能测试****************************
			//10^7
			{

				// myVector  10^7
				STL::Timer::start();
				STL::vector<std::string> myStrVec;

				for (int i = 0; i < 10000000; ++i) {
					myStrVec.push_back(str);
				}
				STL::Timer::finish();
				STL::Timer::PrintUsedTimeOnStream(std::cout);

				//std::vector 10^7
				STL::Timer::start();
				std::vector<std::string> stdStrVec;
				for (int i = 0; i < 10000000; ++i) {
					stdStrVec.push_back(str);
				}
				STL::Timer::finish();
				STL::Timer::PrintUsedTimeOnStream(std::cout);
				/*
				10000000数量级情况下
				两者对比如下：
				myVector:    926 ms
				std::vector: 880 ms
				*/
			}

			//10^6
			{
				//myVector  10^6
				STL::Timer::start();
				STL::vector<std::string> myStrVec;
				for (int i = 0; i < 1000000; ++i) {
					myStrVec.push_back(str);
				}
				STL::Timer::finish();
				STL::Timer::PrintUsedTimeOnStream(std::cout);

				//std::vector 10^6
				STL::Timer::start();
				std::vector<std::string> stdStrVec;
				for (int i = 0; i < 1000000; i++) {
					stdStrVec.push_back(str);
				}
				STL::Timer::finish();
				STL::Timer::PrintUsedTimeOnStream(std::cout);
				/*
				两者对比如下：
				myVector:    82 ms
				std::vector: 78 ms
				*/
			}

			//10^5
			{
				//myVector  10^5
				STL::Timer::start();
				STL::vector<std::string> myStrVec;
				for (int i = 0; i < 100000; i++) {
					myStrVec.push_back(str);
				}
				STL::Timer::finish();
				STL::Timer::PrintUsedTimeOnStream(std::cout);

				//std::vector 10^5
				STL::Timer::start();
				std::vector<std::string> stdStrVec;
				for (int i = 0; i < 100000; i++) {
					stdStrVec.push_back(str);
				}
				STL::Timer::finish();
				STL::Timer::PrintUsedTimeOnStream(std::cout);
				/*
				两者对比如下：
				myVector:    10 ms
				std::vector: 5 ms
				*/
			}
#endif // TEST_ALL

		}
	}
}