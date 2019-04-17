#include <iostream>
#include "ApplicationMonitor.h"

ApplicationMonitor::ApplicationMonitor(ProcessId pid)
{
	this->_hasError = false;
	this->_isEnded = false;
	this->_pidWatching = pid;
}

ApplicationMonitor::~ApplicationMonitor()
{
}

void ApplicationMonitor::WatchProcess()
{
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, this->_pidWatching);
	if (NULL == hProcess) {
		std::cerr << "Unable to read process information." << std::endl;
		this->_isEnded = true;
		this->_hasError = true;
		return;
	}
	DWORD dwExitCode;
	BOOL success = GetExitCodeProcess(hProcess, &dwExitCode);
	CloseHandle(hProcess);
	if (!success) {
		std::cerr << "Unable to read process running status." << std::endl;
		this->_isEnded = true;
		this->_hasError = true;
		return;
	}

	if (dwExitCode != STILL_ACTIVE) {
		std::cout << "Process is now inactive." << std::endl;
		this->_isEnded = true;
	}
}

bool ApplicationMonitor::HasError()
{
	return this->_hasError;
}

bool ApplicationMonitor::IsEnded()
{
	return this->_isEnded;
}
