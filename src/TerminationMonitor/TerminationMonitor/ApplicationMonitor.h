#pragma once
#include <Windows.h>

typedef DWORD ProcessId;
typedef DWORD CtrlType;

class ApplicationMonitor
{
private:
	volatile bool _isEnded;
	volatile bool _hasError;
	ProcessId _pidWatching;

public:
	ApplicationMonitor(ProcessId pid);
	~ApplicationMonitor();

	void WatchProcess();
	bool HasError();
	bool IsEnded();
};

