#include "msgQueue.h"

/*
** 构造函数和析构函数其实没啥东西
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
** 下面是对Queue STL的基本操作的一些封装
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