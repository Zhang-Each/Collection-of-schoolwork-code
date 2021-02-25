#pragma once
#include <iostream>
#include <queue>
#include <thread>
#include <string>

using namespace std;

/*
* 定义了消息队列的基本数据结构
*/
struct msgNode {
	string msg;
};

class msgQueue {
private:
	queue<msgNode> message;
public:
	msgQueue();
	~msgQueue();
	void Enqueue(char* msg);
	void Enqueue(string msg);
	string Dequeue();
};

