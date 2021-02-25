//
// Created by 74096 on 2020/7/1.
//

#include "XMLSerialization.h"
#include<cstdlib>

// 构造函数
XMLSerialization::XMLSerialization()
{
    document = nullptr;
    //root = nullptr;
    // 默认的文件名，可以进行修改
    fileName = "TestXML.xml";
}

// 对XML文档进行初始化的设置，kind为0表示序列化，1表示反序列化
void XMLSerialization::XMLInitialSet(const char* fileName, int kind)
{
    // 序列化时创建对应的XML文件
    if(!kind)
    {
        this->fileName = fileName;
        document = new XMLDocument;
        const char* declaration ="<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>";
        document->Parse(declaration);
        XMLElement* head = document->NewElement("serialization");
        document->InsertFirstChild(head);
        document->InsertEndChild(head);
        document->SaveFile(fileName);

        // 测试了所有的基本类型
        tryWriteBasicType();

        return ;
    }
    // 反序列化时解析对应的XML文件
    else
    {
        document = new XMLDocument;
        document->LoadFile(fileName);
        ptr= document->RootElement()->FirstChildElement();

        // 测试了所有的基本类型
        tryReadBasicType();
        return;
    }
}

// 写入单个int变量
XMLElement* XMLSerialization::writeLine(int val)
{
    XMLElement *result = document->NewElement("std_int");
    result->SetAttribute("value", val);
    return result;
}

// 写入单个float变量
XMLElement* XMLSerialization::writeLine(float val)
{
    XMLElement *result = document->NewElement("std_float");
    result->SetAttribute("value", val);
    return result;
}

// 写入单个bool变量
XMLElement * XMLSerialization::writeLine(bool val)
{
    XMLElement *result = document->NewElement("std_bool");
    result->SetAttribute("value", val);
    return result;
}

// 写入单个char变量
XMLElement * XMLSerialization::writeLine(char val)
{
    XMLElement *result = document->NewElement("std_char");
    result->SetAttribute("value", val);
    return result;
}

// string类型的XML序列化
void XMLSerialization::writeXML(string val)
{
    document->LoadFile(fileName.c_str());
    XMLElement* root = document->RootElement();
    XMLElement* node = writeLine(val);
    root->InsertEndChild(node);
    document->SaveFile(fileName.c_str());
}

// string类型的单个序列化，将其转化为const char*类型进行序列化
XMLElement * XMLSerialization::writeLine(string val)
{
    XMLElement *result = document->NewElement("std_string");
    result->SetAttribute("value", val.c_str());
    return result;
}

// 写入类型名为typename的自定义类型
XMLElement * XMLSerialization::writeUserDefinedType(string typeName)
{
    XMLElement* result = document->NewElement("user_defined_type");
    result->SetAttribute("typename", typeName.c_str());
    return result;
}

// 测试函数，各种基本类型的XML序列化
void XMLSerialization::tryWriteBasicType()
{
    writeXML(123);
    writeXML(float (12.3455));
    writeXML(true);
    writeXML('a');

    vector<int> a = {1,2,3};
    writeXML(a);

    list<int> b;
    b.push_back(1);
    b.push_back(99);
    b.push_back(123);
    writeXML(b);

    // 多层嵌套的vector
    vector<vector<vector<int>>> c;
    vector<vector<int>> d;
    d.push_back({1,2,3});
    d.push_back({4,5,6});
    c.push_back(d);
    c.push_back(d);
    writeXML(c);
    // 多层嵌套的list
    list<list<int>> e;
    e.push_back(b);
    e.push_back(b);
    writeXML(e);
    // string 测试
    string f = "hello world!";
    writeXML(f);

    pair<int, string> g(1, "zyc");
    writeXML(g);

    map<int, string> h;
    h[1]="abc";
    h[2]="def";
    writeXML(h);

    set<int> i;
    i.insert(1);
    i.insert(2);
    writeXML(i);
}

// 测试函数，基本类型的反序列化
void XMLSerialization::tryReadBasicType()
{

    cout<<"---------Show the result of XML Deserialization for basic types---------"<<endl;

    int a;
    float b;
    bool c;

    readXML(a);
    readXML(b);
    readXML(c);
    cout << "int test result "<< a<< '\n'<<"float test result " << b<< '\n'<< "bool test result: " << c <<endl;

    char d;
    readXML(d);
    cout << d <<endl;

    vector<int> e ;
    readXML(e);
    cout<<"vector test result: "<<endl;
    for(int i=0; i<e.size(); i++){
        cout <<e[i]<<" ";
    }
    cout<<endl;

    cout<<"list test result: "<<endl;
    list<int> f;
    readXML(f);
    for(auto it=f.begin(); it!=f.end(); it++){
        cout <<*it<<" ";
    }
    cout<<endl;

    cout<<"nested-vector test result: "<<endl;
    // 多层嵌套的vector
    vector<vector<vector<int>>> g;
    readXML(g);
    cout<<g.size()<<" "<<g[0].size()<<" "<<g[0][0].size()<<endl;

    cout<<"nested-list test result: "<<endl;
    // 多层嵌套的list
    list<list<int>> h;
    readXML(h);
    cout<<h.size()<<" "<<(*h.begin()).size()<<endl;

    // string 测试
    string i ;
    readXML(i);
    cout<<"string test result: "<<i<<endl;

    cout<<"pair test result: "<<endl;
    pair<int, string> j;
    readXML(j);
    cout<<j.first<<" "<<j.second<<endl;

    cout<<"map test result: "<<endl;
    map<int, string> k;
    readXML(k);
    cout<<"size of the map "<<k.size()<<endl;
    cout<<(*k.begin()).first<<" "<<(*k.begin()).second<<endl;

    cout<<"set test result: "<<endl;
    set<int> l;
    readXML(l);
    cout<<"size of the set:" << l.size()<<endl;
}

// 反序列化单个char类型
void XMLSerialization::readXML(char &result) {
    int temp;
    readXML(temp);
    result = (char)temp;
}

// 反序列化string类型
void XMLSerialization::readXML(string &result) {
    const XMLAttribute *attribute = ptr->FirstAttribute();
    result = attribute->Value();
    if(ptr->NextSiblingElement())
        ptr=ptr->NextSiblingElement();
}

