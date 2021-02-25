//
// Created by 74096 on 2020/5/30.
//

#include "Table.h"
dataType::dataType(int input_type, int input_n, string input_typeName, bool input_isUnique, bool input_isPrimaryKey, bool input_hasIndex)
{
    type = input_type;
    n = input_n;
    typeName = input_typeName;
    isUnique = input_isUnique;
    isPrimaryKey = input_isPrimaryKey;
    hasIndex = input_hasIndex;
}

void dataType::showDataType()
{
    cout<<"----------show data type-----------"<<endl;
    cout<<"type: "<<type<<endl;
    cout<<"n: "<<n<<endl;
    cout<<"typename: "<<typeName<<endl;
    cout<<"unique: "<<isUnique<<endl;
    cout<<"primary: "<<isPrimaryKey<<endl;
    cout<<"index: "<<hasIndex<<endl;
}

int dataType::getDataLength()
{
    if(type == miniSQL_INT || type == miniSQL_FLOAT){
        return 4;
    }
    else return n;
}

Table::Table(string name, vector<dataType *> *attribute, vector<string> *index)
{
    tableName = name;
    columnCount = attribute->size();
    tableAttribution = attribute;
    indexAttribution = index;
    size = 0;
    primaryKey = -1;
    int attrType;
    for(int i = 0; i < columnCount; i ++){
        if((*tableAttribution)[i]->isPrimaryKey){
            if(primaryKey == -1)
                primaryKey = i;
            else
                cout<<"Run time error! Too many primary keys!"<<endl;
        }
        attrType = (*tableAttribution)[i]->type;
        if(attrType == miniSQL_INT || attrType == miniSQL_FLOAT){
            size += 4;
        }
        else if(attrType == miniSQL_CHAR){
            size += (*tableAttribution)[i]->n;
        }
        else{
            cout<<"Run time error! Wrong variable type!"<<endl;
        }
    }
    //这里需要空出一格，表示结尾，后面读的时候会把这一格子跳过
    size += 1;
    if(primaryKey == -1){
        cout<<"Run time error! No primary key!"<<endl;
    }
    //判断每张表的最大容量，如果
    if(size > blockSize){
        cout<<"Run time error! Table size is too big!"<<endl;
    }
    numPerBlock = blockSize / size;

}

dataType* Table::searchAttribution(const char *name)
{
    string nameString = (string)name;
    return searchAttribution(nameString);
}

dataType* Table::searchAttribution(const string& name)
{
    for(int i = 0; i < tableAttribution->size(); i ++){
        if((*tableAttribution)[i]->typeName == name){
            return (*tableAttribution)[i];
        }
    }
    return nullptr;
}

int Table::searchPosition(const char *name)
{
    string nameString = string(name);
    return searchPosition(nameString);
}

int Table::searchPosition(const string &name)
{
    for(int i = 0; i < tableAttribution->size(); i ++){
        if((*tableAttribution)[i]->typeName == name){
            return i;
        }
    }
    return -1;
}

void Table::dropIndex(const string &indexName)
{
    dataType* tmp = searchAttribution(indexName);
    tmp->hasIndex = false;
    int i;
    for(i = 0; i < indexAttribution->size(); i ++){
        if(indexAttribution->at(i) == indexName){
            break;
        }
    }
    indexAttribution->erase(indexAttribution->begin() + i);
}