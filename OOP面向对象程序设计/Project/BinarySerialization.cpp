//
// Created by 74096 on 2020/7/1.
//

#include "BinarySerialization.h"


// 用kind来表示当前对象是用来序列化还是反序列化
// 0表示序列化，1表示反序列化
void BinarySerialization::SetTarget(string name, int kind)
{
    fileName = name;
    if(!kind)
        fout.open(fileName.c_str(), ios::binary);
    else
        fin.open(fileName.c_str(), ios::binary);
}

// 停止序列化，需要在序列化结束的时候调用
void BinarySerialization::StopSerialization()
{
    if(fout.is_open())
        fout.close();
    else
        cout<<"Error! The file is closed!"<<endl;
}

// 停止反序列化，需要在反序列化结束的时候调用
void BinarySerialization::StopDeserialization()
{
    if(fin.is_open())
        fin.close();
    else
        cout<<"Error! The file is closed!"<<endl;
}

// string类型的序列化函数
void BinarySerialization::write(string &val)
{
    const char* value = val.c_str();
    int len=sizeof(value);
    write(len);
    fout.write((char*)&value, len);
}

// string类型的反序列化函数
string BinarySerialization::read(string &result)
{
    int size=read(size);
    cout<<"len of the string is "<<size<<endl;
    const char* temp;
    fin.read((char*)&temp, size);
    result = string(temp);
    return result;
}