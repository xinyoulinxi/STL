//º∆ ±¿‡
#ifndef _TIMER_H_
#define _TIMER_H_
#include<time.h>
#include<iostream>
namespace STL {
	class Timer {
	private:

		static clock_t m_startTime;
		static clock_t m_endTime;
		static clock_t m_usedTime;
	public:

		static void start() {
			m_startTime = clock();
		}
		static void finish() {
			m_endTime = clock();
			m_usedTime = m_endTime - m_startTime;
		}
		static clock_t GetUsedTimeMillsecond() {
			return m_usedTime;
		}
		static clock_t GetUsedTimeSecond() {
			return m_usedTime / 1000;
		}
		static void  PrintUsedTimeOnStream(std::ostream& out) {
			out << m_usedTime << " ms " << std::endl;
		}
	};
	clock_t Timer::m_startTime;
	clock_t Timer::m_endTime;
	clock_t Timer::m_usedTime;

}
#endif // !_TIMER_H_