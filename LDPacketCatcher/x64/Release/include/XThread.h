#pragma once

#include <Windows.h>

class XThread
{
public:
	XThread();
	~XThread();

	void Start();
	void Stop();

	void resume();
	void suspend();
	virtual void DoWork(LPARAM lParam);

	LPARAM lParam;
	bool Working;
	volatile bool IsRun;
	HANDLE m_Thread;
};
