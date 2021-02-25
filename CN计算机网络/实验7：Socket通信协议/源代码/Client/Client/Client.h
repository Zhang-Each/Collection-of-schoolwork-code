#pragma once

#include <stdio.h>
#include <windows.h>
#include <thread>
#include <mutex>
#include <chrono>

#include "msgQueue.h"

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

class Client {
private:
	SOCKET sock;
	msgQueue info;
	timed_mutex io_mutex;
	timed_mutex queue_mutex;
public:
	void clientPrintHint();
	int clientConnect(int port, const char* address);
	int clientSend(const char* msg, int length);
	void clientClose();
	// int clientReceive(char* info);
	void clientListenStart(bool& isConnect);
	void queueProcess(char* info, bool& isConnect);
	bool testLock();
};

