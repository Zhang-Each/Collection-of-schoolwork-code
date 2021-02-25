#include "msgQueue.h"

/*
** ���캯��������������ʵûɶ����
*/
msgQueue::msgQueue() {

}

msgQueue::~msgQueue() {

}

void msgQueue::Enqueue(char* newMsg) {
	msgNode temp;
	temp.msg = newMsg;
	message.push(temp);
}


/*
** �����Ƕ�Queue STL�Ļ���������һЩ��װ
*/
void msgQueue::Enqueue(string msg) {
	msgQueue::Enqueue(msg.c_str());
}

string msgQueue::Dequeue() {
	if (message.empty()) {
		return "";
	}
	else {
		msgNode temp = message.front();
		message.pop();
		return temp.msg;
	}
}