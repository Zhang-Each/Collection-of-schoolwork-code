//
// Created by 74096 on 2020/7/1.
//

#ifndef PROJECT_BINARYSERIALIZATION_H
#define PROJECT_BINARYSERIALIZATION_H
#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<string>
#include<list>
#include<set>

using namespace std;

// 将原本分离的序列化类和反序列化类整合成一个完整的类
class BinarySerialization {
private:
    string fileName;
    ifstream fin;
    ofstream fout;
public:
    //BinarySerialization(string name, int kind);
    void SetTarget(string name, int kind);
    void StopSerialization();
    void StopDeserialization();

    // 序列化相关的成员函数
    // 支持一般的变量类型包括int，float，char和其const
    template<class T>
    void write(T& val);
    // 重载的string读写，为了和模板区分开来，写的时候先把sizeof(val)作为int写入，然后根据长度读取string
    void write(string& val);

    template<class A, class B>
    void write(pair<A, B>& val);

    template<class T>
    void write(vector<T>& val);

    template<class T>
    void write(list<T>& val);

    template<class T>
    void write(set<T>& val);

    template<class A, class B>
    void write(map<A, B>& val);

    // 反序列化相关的成员函数
    template<class T>
    T read(T& result);
    // string的read函数
    string read(string& result);
    template<class A, class B>
    pair<A, B> read(pair<A, B>& result);

    template<class T>
    void read(vector<T>& result);

    template<class T>
    void read(list<T>& result);

    template<class T>
    void read(set<T>& result);

    template<class A, class B>
    void read(map<A, B>& result);
    // 用于继承给自定义类型的虚函数，可以在自定义类型中重新定义
    virtual void write_class() {  };
    virtual void read_class() {  };

};

template<class T>
void BinarySerialization::write(T &val)
{
    fout.write((char*)&val, sizeof(T));
}

// pair的读写方法是把两个AB类型的值分别存储
template<class A, class B>
void BinarySerialization::write(pair<A, B>& val)
{
    // int size=sizeof(val);
    // cout<<"size of the pair is "<<size<<endl;
    // write(size);
    // fout.write((char*)&val, size);
    A value_a = val.first;
    B value_b = val.second;
    write(value_a);
    write(value_b);
}


// vector的序列化方法：先写入vector的长度，然后对vector中的元素一个个进行序列化
template<class T>
void BinarySerialization::write(vector<T>& val)
{
    //int size=sizeof(val);
    //cout<<"The size of the vector is "<<size<<endl;
    //write(size);
    //fout.write((char*)&val, size);
    int i, len = val.size();
    write(len);
    for(i=0; i<len ;i++)
    {
        write(val[i]);
    }
}

// list的序列化方法：先写入list的长度，然后对list中的元素一个个进行序列化
template<class T>
void BinarySerialization::write(list<T> &val)
{
    //int size=sizeof(val);
    //cout<<"The size of the list is "<<size<<endl;
    //write(size);
    //fout.write((char*)&val, size);
    int len=val.size();
    write(len);
    for(auto iter=val.begin(); iter!=val.end(); iter++)
    {
        write(*iter);
    }
}

// set的序列化方法：先写入set的长度，然后对set中的元素一个个进行序列化
template<class T>
void BinarySerialization::write(set<T> &val)
{
    //int size=sizeof(val);
    //cout<<"The size of the set is "<<size<<endl;
    //write(size);
    //fout.write((char*)&val, size);
    int len = val.size();
    write(len);
    for(auto iter=val.begin(); iter!=val.end(); iter++)
    {
        write(*iter);
    }
}

// map的序列化方法：先写入map的长度，然后把map中的元素当作pair来写入
template<class A, class B>
void BinarySerialization::write(map<A, B> &val)
{
    //int size=sizeof(val);
    //cout<<"The size of the map is "<<size<<endl;
    //write(size);
    //fout.write((char*)&val, size);
    int len = val.size();
    write(len);
    for(auto m=val.begin(); m!=val.end(); m++)
    {
        pair<A, B> temp = make_pair(m->first, m->second);
        write(temp);
    }
}

// 基本类型的反序列化，直接二进制文件读出
template<class T>
T BinarySerialization::read(T& result)
{
    fin.read((char*)&result, sizeof(T));
    return result;
}

// pair类型的反序列化，分别读出变量类型为A,B的两个变量，然后构造出结果
template<class A, class B>
pair<A, B> BinarySerialization::read(pair<A, B>& result)
{
    //int size=read(size);
    //fin.read((char*)&result, size);
    //return result;
    A temp_a;
    B temp_b;
    read(temp_a);
    read(temp_b);
    result = make_pair(temp_a, temp_b);
    return result;
}

// vector反序列化的方法：先读出vector的长度len, 然后一个个读进来
template<class T>
void BinarySerialization::read(vector<T>& result)
{
    int i, len=read(len);
    //cout<<"size of the vector "<<size<<endl;
    //fin.read((char*)&result, size);
    for(i=0; i<len; i++){
        T temp;
        read(temp);
        result.push_back(temp);
    }
}

// list反序列化的方法：先读出list的长度len, 然后一个个读进来
template<class T>
void BinarySerialization::read(list<T> &result)
{
    //cout<<"Begin in the list"<<endl;
    //int size=read(size);
    //fin.read((char*)&result, size);
    //cout<<"Test list:"<<result.size()<<endl;
    int i, len;
    fin.read((char*)&len, sizeof(int));
    for(i=0; i<len; i++){
        T temp;
        read(temp);
        result.push_back(temp);
    }
}

// set反序列化的方法：先读出set的长度len, 然后一个个读进来
template<class T>
void BinarySerialization::read(set<T> &result)
{
    int i, size=read(size);
    if(result.empty() != 0)
        result.clear();
    for(i=0; i<size; i++)
    {
        T temp;
        read(temp);
        result.insert(temp);
    }
}

// map反序列化的方法：先读出map的长度len, 然后一个个读进来
template<class A, class B>
void BinarySerialization::read(map<A, B> &result)
{
    int i, len = read(len);
    if(result.empty() != 0)
        result.clear();
    for(i=0; i<len; i++){
        A temp_a;
        B temp_b;
        read(temp_a);
        read(temp_b);
        result[temp_a] = temp_b;
    }
}


#endif //PROJECT_BINARYSERIALIZATION_H
