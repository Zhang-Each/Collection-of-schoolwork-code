//
// Created by 74096 on 2020/7/1.
//

#ifndef PROJECT_TESTCLASS_H
#define PROJECT_TESTCLASS_H
#include"BinarySerialization.h"
#include"XMLSerialization.h"
#include<string>
#include<iostream>
#include<vector>

using namespace std;

// 用于测试自定义类型的二进制和XML的序列化和反序列化的两个类
class TestClass: public BinarySerialization {
public:
    int num;
    double price;
    string id;
    vector<int> array;
    TestClass();
    TestClass(int a, double b, string c);
    void TestBasicType();

    void show(int a, double b, string c, vector<int> d);
    void setDeserializeResult(int a, double b, string c, vector<int> d);
    // 覆写的二进制序列化函数
    void write_class() override {
        show(num,price,id,array);
        string fileName = "TestBinary.data";
        SetTarget(fileName, 0);
        write(num);
        write(price);
        write(id);
        write(array);
        cout<<"Finish Serialize!"<<endl;
        StopSerialization();
    }

    // 覆写的二进制反序列化函数
    void read_class() override{
        string fileName = "TestBinary.data";
        SetTarget(fileName, 1);
        int a = read(a);
        double b = read(b);
        string c ; read(c);
        vector<int> d;
        read(d);
        setDeserializeResult(a , b, c, d);
        show(num,price,id,array);
        StopDeserialization();
        cout<<"Finish Deserialize!"<<endl;
    }

};

class TestClass2: public XMLSerialization{
public:
    int num;
    double price;
    string id;
    vector<int> array;
    TestClass2();
    TestClass2(int a, double b, string c);
    void show(int a, double b, string c, vector<int> d);
    void setDeserializeResult(int a, double b, string c, vector<int> d);
    void writeAllTypes(){
        XMLInitialSet("TestXML.xml", 0);
        document->LoadFile(fileName.c_str());
        writeUserDefinedClass();
    }
    void readAllTypes(){
        XMLInitialSet("TestXML.xml", 1);
        readUserDefinedClass();
    }

    // 覆写的XML序列化函数
    void writeUserDefinedClass() override {
        XMLElement* root = document->RootElement();
        XMLElement* classHead = writeUserDefinedType("TestClass");
        XMLElement* attribution[4];
        attribution[0] = writeUserDefinedType("num");
        attribution[0]->InsertEndChild(writeLine(num));
        attribution[1] = writeUserDefinedType("price");
        attribution[1]->InsertEndChild(writeLine(float (price)));
        attribution[2] = writeUserDefinedType("id");
        attribution[2]->InsertEndChild(writeLine(id));
        attribution[3] = writeUserDefinedType("array");
        attribution[3]->InsertEndChild(writeLine(array));
        int i;
        for(i=0; i<4; i++)
            classHead->InsertEndChild(attribution[i]);
        root->InsertEndChild(classHead);
        document->SaveFile(fileName.c_str());
    }

    // 覆写的XML反序列化函数
    void readUserDefinedClass() override{
        int num1;
        double price1;
        string id1;
        vector<int> array1;

        ptr=ptr->FirstChildElement()->FirstChildElement();
        readXML(num1);
        ptr=ptr->Parent()->NextSiblingElement()->FirstChildElement();
        readXML(price1);
        ptr=ptr->Parent()->NextSiblingElement()->FirstChildElement();
        readXML(id1);
        ptr=ptr->Parent()->NextSiblingElement()->FirstChildElement();
        readXML(array1);
        show(num1,price1,id1,array1);
        if(ptr->NextSiblingElement())
            ptr=ptr->NextSiblingElement();
    }

};


#endif //PROJECT_TESTCLASS_H
