#include "MHighResolutionTimer.h"


MHighResolutionTimer::MHighResolutionTimer()
{
	m_started = false;
}

MHighResolutionTimer::~MHighResolutionTimer()
{
	m_started = false;
}

void MHighResolutionTimer::Start()
{
	m_started = true;
	QueryPerformanceCounter(&m_t1);
}

double MHighResolutionTimer::ElapsedTime()
{
	if (m_started == false)
		return 0.0;

	QueryPerformanceCounter(&m_t2);
	LARGE_INTEGER frequency;  
	double elapsedTime;
	QueryPerformanceFrequency(&frequency);
	elapsedTime = (double) (m_t2.QuadPart - m_t1.QuadPart) / (double) frequency.QuadPart;
	return elapsedTime;
}




