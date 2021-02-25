//
// Created by 74096 on 2020/5/24.
//

#ifndef CODE_INTERPRETER_H
#define CODE_INTERPRETER_H
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>

#include "../StringProcessor/StringProcessor.h"
#include "../API/API.h"
#include "showResult.h"
#include "callAPI.h"


using namespace std;


class Interpreter {
public:
    //这里本来想写成static 类型的，但是后来发现static类型需要定义在类的内部，就改成了普通的成员函数类型
    string getCMD();
    bool execute(string cmd);

private:
    //读取文件中的SQL语句并进行对应的操作
    void exeFile(const string& file);

};


#endif //CODE_INTERPRETER_H
