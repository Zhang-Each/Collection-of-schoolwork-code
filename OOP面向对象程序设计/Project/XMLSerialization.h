//
// Created by 74096 on 2020/7/1.
//

#ifndef PROJECT_XMLSERIALIZATION_H
#define PROJECT_XMLSERIALIZATION_H

#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<string>
#include<list>
#include<set>

#include"tinyxml2.h"

using namespace std;
using namespace tinyxml2;


// 用于进行XML序列化的类，可以继承给自定义类型来进行自定义类型和XML序列化和反序列化

class XMLSerialization {
public:
    XMLDocument* document;
    XMLElement* ptr;
    string fileName;
    XMLSerialization();
    // 初始化设置，设置的内容包括文件名和操作种类
    void XMLInitialSet(const char* fileName, int kind);

    // XML序列化的一系列重载函数，分别对应了各种基本变量类型和string以及STL
    // 采用了模板+重载的C++特性
    template<class T>
    void writeXML(T val);
    void writeXML(string val);

    template<class T>
    void writeXML(vector<T> vec);

    template<class T>
    void writeXML(list<T> val);

    template<class T>
    void writeXML(set<T> val);

    template<class A, class B>
    void writeXML(pair<A, B> val);

    template<class A, class B>
    void writeXML(map<A, B> val);

    // XML序列化中对于组合类型的单个变量进行序列化的一系列函数，用于在一个由多个元素组成的结构中序列化单个元素
    // 采用模板+重载的C++特性
    XMLElement* writeLine(int val);
    XMLElement* writeLine(float val);
    XMLElement* writeLine(char val);
    XMLElement* writeLine(bool val);
    XMLElement* writeLine(string val);

    template<class T>
    XMLElement* writeLine(vector<T> val);

    template<class T>
    XMLElement* writeLine(list<T> val);

    template<class T>
    XMLElement* writeLine(set<T> val);

    template<class A, class B>
    XMLElement* writeLine(pair<A, B> val);

    //因为map的写单个元素可以转化成pair，因此不需要这个成员函数
    //template<class A, class B>
    //XMLElement* writeLine(map<A, B> val);

    //反序列化相关的成员函数
    //从XML文件中读出一个基本类型，string或者STL的成员函数
    template<class T>
    void readXML(T &result);
    void readXML(char &result);
    void readXML(string& result);


    template<class T>
    void readXML(vector<T> &result);

    template<class T>
    void readXML(list<T>& result);

    template<class T>
    void readXML(set<T> &result);

    template<class A, class B>
    void readXML(pair<A, B> &result);

    template<class A, class B>
    void readXML(map<A, B> &result);


    //序列化一个用户自定义名称的变量类型，可以是类
    XMLElement* writeUserDefinedType(string typeName);

    // 虚函数，可以被继承的子类覆写，用于在子类中定义自定义类型的XML序列化和反序列化
    virtual void writeUserDefinedClass(){

    }

    virtual void readUserDefinedClass(){

    }

    // 基本类型的测试函数，调用时可以测试出所有的基本类型
    void tryWriteBasicType();
    void tryReadBasicType();

};

// 基本类型int，float，char，bool等类型的XML序列化
template<class T>
void XMLSerialization::writeXML(T val)
{
    document->LoadFile(fileName.c_str());
    XMLElement* root = document->RootElement();
    XMLElement* node = writeLine(val);
    root->InsertEndChild(node);
    document->SaveFile(fileName.c_str());
}

// vector类型的XML序列化
template<class T>
void XMLSerialization::writeXML(vector<T> vec)
{
    document->LoadFile(fileName.c_str());
    XMLElement* root = document->RootElement();
    XMLElement* head = document->NewElement("std_vector");
    head->SetAttribute("size", to_string(vec.size()).c_str());
    int i;
    for(i=0; i<vec.size(); i++)
    {
        head->InsertEndChild(writeLine(vec[i]));
    }
    root->InsertEndChild(head);
    document->SaveFile(fileName.c_str());
}

// list类型的XML序列化
template<class T>
void XMLSerialization::writeXML(list<T> val)
{
    document->LoadFile(fileName.c_str());
    XMLElement* root = document->RootElement();
    XMLElement* head = document->NewElement("std_list");
    head->SetAttribute("size", to_string(val.size()).c_str());
    for(auto i = val.begin(); i!= val.end(); i++)
    {
        head->InsertEndChild(writeLine(*i));
    }
    root->InsertEndChild(head);
    document->SaveFile(fileName.c_str());
}

// pair类型的XML序列化

template<class A, class B>
void XMLSerialization::writeXML(pair<A, B> val)
{
    document->LoadFile(fileName.c_str());
    XMLElement* root = document->RootElement();
    XMLElement* head = writeLine(val);
    root->InsertEndChild(head);
    document->SaveFile(fileName.c_str());
}

// map类型的XML序列化
template<class A, class B>
void XMLSerialization::writeXML(map<A, B> val)
{
    document->LoadFile(fileName.c_str());
    XMLElement* root = document->RootElement();
    XMLElement* head = document->NewElement("std_map");
    head->SetAttribute("size", to_string(val.size()).c_str());
    for(auto m=val.begin(); m!=val.end(); m++)
    {
        pair<A, B> temp = make_pair(m->first, m->second);
        head->InsertEndChild(writeLine(temp));
    }

    root->InsertEndChild(head);
    document->SaveFile(fileName.c_str());
}

// set类型的XML序列化
template<class T>
void XMLSerialization::writeXML(set<T> val)
{
    document->LoadFile(fileName.c_str());
    XMLElement* root = document->RootElement();
    XMLElement* head = document->NewElement("std_set");
    head->SetAttribute("size", to_string(val.size()).c_str());
    for(auto i = val.begin(); i!= val.end(); i++)
    {
        head->InsertEndChild(writeLine(*i));
    }
    root->InsertEndChild(head);
    document->SaveFile(fileName.c_str());
}

// 单个基本类型的序列化，用于组合类型的序列化中
template<class T>
XMLElement* XMLSerialization::writeLine(vector<T> val)
{
    XMLElement *result = document->NewElement("std_vector");
    result->SetAttribute("size", to_string(val.size()).c_str());
    int i;
    for(i=0; i<val.size(); i++)
    {
        result->InsertEndChild(writeLine(val[i]));
    }
    return result;
}

// 单个list类型的序列化，用于组合类型的序列化中
template<class T>
XMLElement* XMLSerialization::writeLine(list<T> val)
{
    XMLElement *result = document->NewElement("std_list");
    result->SetAttribute("size", to_string(val.size()).c_str());
    for(auto i=val.begin(); i!=val.end(); i++)
    {
        result->InsertEndChild(writeLine(*i));
    }
    return result;
}

// 单个pair类型的序列化，用于组合类型的序列化中
template<class A, class B>
XMLElement* XMLSerialization::writeLine(pair<A, B> val)
{
    XMLElement* result = document->NewElement("std_pair");
    XMLElement* first = document->NewElement("first");
    first->InsertEndChild(writeLine(val.first));
    XMLElement* second = document->NewElement("second");
    second->InsertEndChild(writeLine(val.second));
    result->InsertEndChild(first);
    result->InsertEndChild(second);
    return result;
}

// 单个set类型的序列化，用于组合类型的序列化中
template<class T>
XMLElement* XMLSerialization::writeLine(set<T> val)
{
    XMLElement *result = document->NewElement("std_set");
    result->SetAttribute("size", to_string(val.size()).c_str());
    for(auto i=val.begin(); i!=val.end(); i++)
    {
        result->InsertEndChild(writeLine(*i));
    }
    return result;
}

// 基本类型的XML反序列化
template<class T>
void XMLSerialization::readXML(T &result) {
    const XMLAttribute *attribute = ptr->FirstAttribute();
    ptr->QueryAttribute(attribute->Name(), &result);
    if(ptr->NextSiblingElement())
        ptr=ptr->NextSiblingElement();
}

// vector类型的XML反序列化，逐一写入所有元素
template<class T>
void XMLSerialization::readXML(vector<T> &result) {
    const XMLAttribute *attribute = ptr->FirstAttribute();
    int size;
    ptr->QueryAttribute(attribute->Name(), &size);
    ptr = ptr->FirstChildElement();
    for(int i = 0; i < size; ++i){
        T temp;
        readXML(temp);
        result.push_back(temp);
    }
    ptr=ptr->Parent()->ToElement();
    if(ptr->NextSiblingElement())
        ptr=ptr->NextSiblingElement();
}

// list类型的XML反序列化，逐一写入所有元素
template<class T>
void XMLSerialization::readXML(list<T> &result) {
    const XMLAttribute *attribute = ptr->FirstAttribute();
    int size;
    ptr->QueryAttribute(attribute->Name(), &size);
    ptr = ptr->FirstChildElement();
    for(int i = 0; i < size; ++i){
        T temp;
        readXML(temp);
        result.push_back(temp);
    }
    ptr=ptr->Parent()->ToElement();
    if(ptr->NextSiblingElement())
        ptr=ptr->NextSiblingElement();
}

// set类型的XML反序列化,逐一写入所有元素
template<class T>
void XMLSerialization::readXML(set<T> &result) {
    const XMLAttribute *attribute = ptr->FirstAttribute();
    int size;
    ptr->QueryAttribute(attribute->Name(), &size);
    ptr = ptr->FirstChildElement();
    for(int i = 0; i < size; ++i){
        T temp;
        readXML(temp);
        result.insert(temp);
    }
    ptr=ptr->Parent()->ToElement();
    if(ptr->NextSiblingElement())
        ptr=ptr->NextSiblingElement();
}

// pair类型的XML反序列化,分别写入pair的first和second
template<class A, class B>
void XMLSerialization::readXML(pair<A, B> &result) {
    A temp_a;
    B temp_b;
    ptr=ptr->FirstChildElement()->FirstChildElement();
    readXML(temp_a);
    ptr=ptr->Parent()->NextSibling()->FirstChildElement();
    readXML(temp_b);
    ptr=ptr->Parent()->Parent()->ToElement();
    result = make_pair(temp_a, temp_b);
    if(ptr->NextSiblingElement())
        ptr=ptr->NextSiblingElement();
}

// map类型的XML反序列化,等价于写入若干组pair<A, B>
template<class A, class B>
void XMLSerialization::readXML(map<A, B> &result) {
    const XMLAttribute *attribute = ptr->FirstAttribute();
    int size;
    ptr->QueryAttribute(attribute->Name(), &size);
    ptr = ptr->FirstChildElement();
    for(int i = 0; i < size; ++i){
        pair<A, B> temp;
        readXML(temp);
        result.insert(temp);
    }
    ptr=ptr->Parent()->ToElement();
    if(ptr->NextSiblingElement())
        ptr=ptr->NextSiblingElement();
}
#endif //PROJECT_XMLSERIALIZATION_H
