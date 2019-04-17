#include <string>
#include <iostream>
#include <Windows.h>
#include "ApplicationMonitor.h"

volatile auto _isEnded = false;

ProcessId ParsePid(const char* arg) {
	auto sarg = std::string(arg);
	auto pid = std::stoi(sarg);
	return (ProcessId)pid;
}

void CtrlHandler(CtrlType ctrlType)
{
	switch (ctrlType)
	{
	case CTRL_C_EVENT:
	case CTRL_CLOSE_EVENT:
	case CTRL_BREAK_EVENT:
	case CTRL_LOGOFF_EVENT:
	case CTRL_SHUTDOWN_EVENT:
		std::cout << "Caught signal" << std::endl;

		for (auto i = 0; i < 10; i++) {
			std::cout << "Waiting for program termination: " << i << std::endl;
			Sleep(1000);
		}

		_isEnded = true;
		break;
	default:
		return;
	}
}

void BlockUntilTermination(ApplicationMonitor& monitor) {
	while (!_isEnded && !monitor.IsEnded()) {
		Sleep(1000);
		monitor.WatchProcess();
	}
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Wrong argument. Please set a PID to watch application." << std::endl;
		return 1;
	}

	BOOL success = SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE);
	if (!success) {
		std::cerr << "Failed to set handler" << std::endl;
		return 1;
	}

	std::cout << "Start monitoring ..." << std::endl;
	auto pid = ParsePid(argv[1]);
	auto monitor = ApplicationMonitor(pid);
	BlockUntilTermination(monitor);
	if (monitor.HasError()) {
		std::cerr << "Monitor is ended with error." << std::endl;
		return 1;
	}
	std::cout << "End monitoring ..." << std::endl;

	return 0;
}
