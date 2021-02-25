//
// Created by 74096 on 2020/7/1.
//

#include "TestClass.h"

TestClass::TestClass()
{
    num = 0;
    price = 0;
    id = "";
}

TestClass::TestClass(int a, double b, string c)
{
    num = a;
    price = b;
    id = c;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);
}

void TestClass::show(int a, double b, string c, vector<int> d)
{
    cout<<"---------Show the result of Serialization and Deserialization---------"<<endl;
    cout<<"The num is "<<a<<endl;
    cout<<"The price is "<<b<<endl;
    cout<<"The id is "<<c<<endl;
    cout<<"The vector is "<<endl;
    for(int i : d)
        cout<<i<<" ";
    cout<<endl;
}

void TestClass::setDeserializeResult(int a, double b, string c, vector<int> d)
{
    num = a;
    price = b;
    id = c;
    array = d;
}

// 测试二进制序列化和反序列化
void TestClass::TestBasicType() {

    cout<<"---------Show the result of Binary Deserialization for basic types---------"<<endl;
    // 序列化解析
    string name="TestBinary.data";
    //cin>>name;
    BinarySerialization test;
    test.SetTarget(name, 0);
    bool a = true;
    int d=89898989;
    float e=1.234;
    char g='a';
    string i="hello world!";
    pair<int, char> k(1,'k');
    vector<float> m={1.1,2.2,3.3,4.4};
    list<int> o;
    o.push_back(1);
    o.push_back(2);
    set<int> p={1,2};
    map<int, char> q;
    q[1]='l';
    q[2]='z';
    test.write(a);
    test.write(d);
    test.write(e);
    test.write(g);
    test.write(i);
    test.write(k);
    test.write(m);
    test.write(o);
    test.write(p);
    test.write(q);
    //cout<<"OK!"<<endl;
    // 每次序列化和反序列化结束后都需要关闭文件
    test.StopSerialization();

    // 反序列化解析
    BinarySerialization test2;
    test2.SetTarget(name, 1);
    bool a0;
    test2.read(a0);
    int b;
    const int c=test2.read(b);
    //test2.read(b);
    float f=test2.read(f);
    char h=test2.read(h);
    string j;
    test2.read(j);
    pair<int, char> l=test2.read(l);
    vector<float> n;
    test2.read(n);
    list<int> r;
    set<int> s;
    map<int, char> t;
    test2.read(r);
    test2.read(s);
    test2.read(t);
    test2.StopDeserialization();

    // 展示结果
    cout<<"bool deserialization: "<<a0<<endl;
    cout<<"int deserialization: "<<b<<" "<<c<<endl;
    cout<<"float deserialization: "<<f<<endl;
    cout<<"char deserialization: "<<h<<endl;
    cout<<"string deserialization: "<<j<<endl;
    cout<<"pair deserialization: "<<l.first<<" "<<l.second<<endl;
    cout<<"vector deserialization: "<<n.size()<<" "<<n[0]<<" "<<n[1]<<endl;

    cout<<"list: ";
    cout<<"size: "<<r.size()<<" the first element: "<<r.front()<<endl;

    cout<<"set: ";
    cout<<"size: "<<s.size()<<endl;

    cout<<"map: ";
    cout<<"size: "<<t.size()<<" t[1]="<<t[1]<<endl;
}

TestClass2::TestClass2()
{
    num = 0;
    price = 0;
    id = "";
}

TestClass2::TestClass2(int a, double b, string c)
{
    num = a;
    price = b;
    id = c;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);
}

void TestClass2::show(int a, double b, string c, vector<int> d)
{
    cout<<"---------Show the result of Serialization and Deserialization---------"<<endl;
    cout<<"The num is "<<a<<endl;
    cout<<"The price is "<<b<<endl;
    cout<<"The id is "<<c<<endl;
    cout<<"The vector is ";
    for(int i : d)
        cout<<i<<" ";
    cout<<endl;
}

void TestClass2::setDeserializeResult(int a, double b, string c, vector<int> d)
{
    num = a;
    price = b;
    id = c;
    array = d;
}