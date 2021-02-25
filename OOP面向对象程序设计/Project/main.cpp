#include<iostream>


#include"BinarySerialization.h"
#include"XMLSerialization.h"
#include"TestClass.h"

using namespace std;


void TestBinary();
void TestXML();
void TestVector();
void TestPair();
void TestSet();
void TestMap();


int main()
{
    int choose;
    // 测试基本类型的二进制序列化和反序列化
    cout<<"Please enter 0 to test XMLSerialization and 1 to test BinarySerialization."<<endl;
    cin>>choose;
    if(choose == 0)
        TestXML();
    else if(choose == 1)
        TestBinary();
    else
        cout<<"Wrong input! Please try again!"<<endl;
    // TestVector();
    // TestPair();
    // TestSet();
    // TestMap();
    system("pause");
    return 0;
}

// 测试二进制的序列化和反序列化
void TestBinary()
{
    string name = "zyc";
    TestClass a(1, 5.7, name);
    // 测试基本类型的二进制序列化和反序列化
    a.TestBasicType();
    a.write_class();

    TestClass b;
    b.read_class();
    cout<<"You can find the binary file TestBinary.data in the same directory of exe file."<<endl;
}

// 测试XML序列化和反序列化
void TestXML()
{
    TestClass2 temp(1, 2.2, "12345");
    temp.writeAllTypes();
    temp.readAllTypes();
    cout<<"You can read the xml file in the same directory of exe file."<<endl;
}

/** 一些废弃的测试函数，主要用来测试单个STL的序列化
void TestVector()
{
    // 单层vector
    string name="TestBinary.data";
    vector<int> a={1,2,3};

    BinarySerialization write_vector;
    write_vector.SetTarget(name, 0);
    write_vector.write(a);
    write_vector.StopSerialization();

    vector<int> b;
    BinarySerialization read_vector;
    read_vector.SetTarget(name, 1);
    read_vector.read(b);
    read_vector.StopDeserialization();

    for(auto i: b)
        cout<<i<<" ";
    cout<<endl;
    // string 类的测试
    vector<string> c = {"zyc", "oop", "project"};
    write_vector.SetTarget(name, 0);
    write_vector.write(c);
    write_vector.StopSerialization();

    vector<string> c_read;
    read_vector.SetTarget(name, 1);
    read_vector.read(c_read);
    read_vector.StopDeserialization();
    cout<<c_read.size()<<endl;
    for(const auto& i: c)
        cout<<i<<" ";
    cout<<endl;

    // 多层嵌套vector的测试
    BinarySerialization write_vector_loop, read_vector_loop;

    vector<vector<string>> d;
    d.push_back(c);
    d.push_back(c);
    write_vector_loop.SetTarget(name, 0);
    write_vector_loop.write(d);
    write_vector_loop.StopSerialization();

    vector<vector<string>> e;
    read_vector_loop.SetTarget(name, 1);
    read_vector_loop.read(e);
    read_vector_loop.StopDeserialization();
    cout<<e.size()<<" "<<e[0].size()<<endl;
}

void TestPair()
{
    pair<int, int> a(1,2), b;
    pair<string, vector<int>> c, d;
    vector<int> e = {1,2,3};
    c.first = "zyc";
    c.second = e;

    BinarySerialization write_pair, read_pair;
    write_pair.SetTarget("TestBinary.data", 0);
    write_pair.write(a);
    write_pair.write(c);
    write_pair.StopSerialization();


    read_pair.SetTarget("TestBinary.data", 1);
    read_pair.read(b);
    read_pair.read(d);
    read_pair.StopDeserialization();
    cout<<b.first<<" "<<b.second<<endl;
    cout<<d.first<<" "<<d.second.size()<<" "<<d.second[1]<<endl;
}


void TestSet()
{
    set<int> a, b;
    for(int i=0; i<10 ;i++)
        a.insert(i);
    BinarySerialization write_set, read_set;
    write_set.SetTarget("TestBinary.data", 0);
    write_set.write(a);
    write_set.StopSerialization();
    read_set.SetTarget("TestBinary.data", 1);
    read_set.read(b);
    read_set.StopDeserialization();
    cout<<b.size()<<endl;
}

void TestMap()
{
    map<int, string> a, b;
    a[1] = "zyc";
    a[2] = "njz";
    BinarySerialization write_map, read_map;

    write_map.SetTarget("TestBinary.data", 0);
    write_map.write(a);
    write_map.StopSerialization();

    read_map.SetTarget("TestBinary.data", 1);
    read_map.read(b);
    read_map.StopDeserialization();

    cout<<b.size()<<" "<<b[1]<<endl;
}
 */