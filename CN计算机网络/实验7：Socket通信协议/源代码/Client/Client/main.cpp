#include <iostream>
#include <thread>
#include <string>

#include "msgQueue.h"
#include "Client.h"
using namespace std;

Client client;
char msg[4096], receive[4096], watch[4096];
bool isConnect = false;

thread* t1 = NULL;
thread* t2 = NULL;

// 建立两个子线程，分别用于监听和处理消息队列中的消息
void listening() {
	client.clientListenStart(isConnect);
}

void processing() {
	client.queueProcess(watch, isConnect);
}

int main()
{
	int result = 0;
	t1 = new thread(listening);
	t2 = new thread(processing);

	if (result == 0) {
		client.clientPrintHint();
		int choice;
		while (true) {
			while (!client.testLock());
			cout << "LocalHost>>>";
			cin >> choice;
			// 按照输入的选择来进行不同的操作
			if (choice == 1) {
				if (isConnect) {
					cout << "Error! You have been connect to the server!\n" << endl;

				}
				// 没有连接到服务端的时候尝试连接到服务端
				else {
					string ip;
					cout << "Please input the IP address:" << endl;
					cin >> ip;
					// cout << "IP: " << ip << endl;
					result = client.clientConnect(3501, ip.c_str());
					if (result != 0) {
						cout << "Fail to connect! Error information: " << result << endl;
						continue;
					}
					cout << "Success to connect!" << endl;
					isConnect = true;
				}
			}
			else if (choice == 2) {
				if (!isConnect) {
					cout << "You are not in connection! \n" << endl;
				}
				else {
					cout << "Waiting for response......" << endl;
					isConnect = false;
					Sleep(1000);
					cout << "Success to disconnect!\n" << endl;
					strcpy(msg, "exit");
					client.clientSend(msg, 4096);
					client.clientClose();
				}
			}
			// 以下三种是向服务器获取数据的方式
			else if (choice == 4) {
				strcpy(msg, "GetName");
				result = client.clientSend(msg, 4096);
				msg[0] = '\0';
			}
			else if (choice == 5) {
				strcpy(msg, "GetList");
				result = client.clientSend(msg, 4096);
				msg[0] = '\0';
			}
			else if (choice == 3) {
				strcpy(msg, "GetTime");
				result = client.clientSend(msg, 4096);
				msg[0] = '\0';
			}
			// 客户端间的通信
			else if (choice == 6) {
				string num, info;
				cout << "Please input the client number: \n";
				cin >> num;
				cout << "Please input your message: \n";
				cin >> info;
				string pack = "Send " + num + " " + info;
				strcpy(msg, pack.c_str());
				result = client.clientSend(msg, 4096);
				msg[0] = '\0';
			}
			else if (choice == 7) {
				if (isConnect) {
					cout << "Waiting for response......" << endl;
					isConnect = false;
					Sleep(1000);
					client.clientClose();
					cout << "CLient closed!" << endl;
				}
				break;
			}
			else {
				cout << "Error: No such operation\n" << endl;
			}
		}
	}
	system("pause");
	return 0;
	
}