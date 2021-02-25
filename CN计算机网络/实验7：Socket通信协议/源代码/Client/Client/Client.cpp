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
	// ����socket
	// cout << "\n\nIn the connection!!!!!" << endl;
	int err = 0;
	WORD request = MAKEWORD(2, 2);
	WSADATA data;
	err = WSAStartup(request, &data);
	if (err != 0) {
		// WSA�����棬����1
		cout << "Fail in Windows Sockets Asynchronous Start Up! Error infomation: " << err << endl;
		return 1;
	}
	else {
		// ����socket
		sock = socket(AF_INET, SOCK_STREAM, 0);
		// ����ʧ�ܣ���Ч��socket������2
		if (sock == INVALID_SOCKET) {
			cout << "Fail in Socket Creating! Error information: " << WSAGetLastError() << endl;
			return 2;
		}
		// �趨������������
		SOCKADDR_IN server;
		server.sin_family = AF_INET;
		server.sin_port = htons(port);
		server.sin_addr.s_addr = inet_addr(address);
		// ���ӷ�����
		err = connect(sock, (SOCKADDR*)& server, sizeof(server));
		if (err != 0) {
			// ���ӷ�������������3
			cout << "Fail in Connection with server! Error infomation: " << err << endl;
			return 3;
		}
		return 0;
	}
	return 0;
}

/*
* �����˷�����Ϣ����ͬ�ķ���ֵ�ֱ������ʧ�ܣ����ӳ�ʱ�ͳɹ������������
* ������socket�е�send������������Ϣ�ķ���
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
		// ��������ʧ��
		if (!queue_mutex.try_lock()) {
			Sleep(500);
			continue;
		}
		res = info.Dequeue();
		// ��Ϣ�����ǿյ�
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
		// ÿ�μ������ʱ��������Ϣ500ms������������߳�һֱ������ը��
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


