#pragma once
#include <windows.h>

class MHighResolutionTimer
{
public:
	MHighResolutionTimer();
	~MHighResolutionTimer();
	void Start();
	double ElapsedTime();
private:
	LARGE_INTEGER m_t1, m_t2;     
	bool m_started;
};