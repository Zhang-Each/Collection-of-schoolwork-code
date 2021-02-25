#include "Client.h"

void Client::clientPrintHint() {
	cout << "Welcome to the DIY Client!" << endl;
	cout << "Author: Zhang Each & Nie Junzhe\n" << endl;
	cout << "You can choose the following operations:\n" << endl;
	cout << "\t1. Connect to the server\n" << endl;
	cout << "\t2. Close the server connect\n" << endl;
	cout << "\t3. Get the time\n" << endl;
	cout << "\t4. Get the server name\n" << endl;
	cout << "\t5. Get the client list\n" << endl;
	cout << "\t6. Send a message to server\n" << endl;
	cout << "\t7. Quit\n" << endl;
}

int Client::clientConnect(int port, const char* address) {
	struct timeval timeout = { 3,0 };
	struct linger my_linger = { TRUE, 30 };
	int test = setsockopt(sock, SOL_SOCKET, SO_DONTLINGER, (char*)&my_linger, sizeof(my_linger));
	if (test) {
		perror("setsocket:");
		cout << endl;
	}
	// 启动socket
	// cout << "\n\nIn the connection!!!!!" << endl;
	int err = 0;
	WORD request = MAKEWORD(2, 2);
	WSADATA data;
	err = WSAStartup(request, &data);
	if (err != 0) {
		// WSA出错警告，返回1
		cout << "Fail in Windows Sockets Asynchronous Start Up! Error infomation: " << err << endl;
		return 1;
	}
	else {
		// 创建socket
		sock = socket(AF_INET, SOCK_STREAM, 0);
		// 创建失败，无效的socket，返回2
		if (sock == INVALID_SOCKET) {
			cout << "Fail in Socket Creating! Error information: " << WSAGetLastError() << endl;
			return 2;
		}
		// 设定服务器的数据
		SOCKADDR_IN server;
		server.sin_family = AF_INET;
		server.sin_port = htons(port);
		server.sin_addr.s_addr = inet_addr(address);
		// 连接服务器
		err = connect(sock, (SOCKADDR*)& server, sizeof(server));
		if (err != 0) {
			// 连接服务器出错，返回3
			cout << "Fail in Connection with server! Error infomation: " << err << endl;
			return 3;
		}
		return 0;
	}
	return 0;
}

/*
* 向服务端发送信息，不同的返回值分别代表发送失败，连接超时和成功发送三种情况
* 调用了socket中的send函数来进行消息的发送
*/
int Client::clientSend(const char* msg, int length) {
	int err = send(sock, msg, length, 0);
	if (err < 0) {
		cout << "Fail to send the message for error " << err << endl;
		return 1;
	}
	else if (err == 0) {
		cout << "Connect time out!" << endl;
		return 3;
	}
	io_mutex.lock();
	return 0;
}


bool Client::testLock() {
	if (!io_mutex.try_lock()) {
		return false;
	}
	else {
		io_mutex.unlock();
		return true;
	}
}

void Client::clientListenStart(bool& isConnect) {
	while (true) {
		string res;
		// 尝试上锁失败
		if (!queue_mutex.try_lock()) {
			Sleep(500);
			continue;
		}
		res = info.Dequeue();
		// 消息队列是空的
		if (res == "") {
			queue_mutex.unlock();
			Sleep(500);
			continue;
		}
		cout << "\nServer>>>" << res << endl;
		queue_mutex.unlock();
		if (!testLock()) {
			io_mutex.unlock();
		}
		else {
			cout << "\nLocalHost>>>" << endl;
		}
		// 每次检查锁的时候检查完休息500ms，不让这个子线程一直运行跑炸了
		Sleep(500);
	}
}

void Client::queueProcess(char* infomation, bool& isConnect) {
	while (true) {
		int err = 0;
		err = recv(sock, infomation, 4096, 0);
		if (err < 0) {
			continue;
		}
		else if (err == 0) {
			cout << "Network Interrupted!" << endl;
		}
		queue_mutex.lock();
		this->info.Enqueue(infomation);
		queue_mutex.unlock();
	}
}

void Client::clientClose() {
	closesocket(sock);
}


