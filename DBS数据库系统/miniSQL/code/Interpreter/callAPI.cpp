//
// Created by 74096 on 2020/6/13.
//

#include "callAPI.h"
// 这两个分别调用drop表和索引的API，比较容易写
bool callAPI::callDropTableAPI(const string& tableName){
    return api->dropTable(tableName);
}
bool callAPI::callDropIndexAPI(const string& indexName){
    return api->dropIndex(indexName);
}

bool callAPI::callCreateIndexAPI(const string& index, const string& table, const string& attribute){
    /*
    cout<<index<<endl;
    cout<<table<<endl;
    cout<<attribute<<endl;
    */
    return api->createIndex(index, table, attribute);
}

bool callAPI::callInsertAPI(const string& tableName, string& value){
    // cout<<tableName<<endl;
    // cout<<value<<endl;
    // 这里直接按照逗号进行分割就可以，传进来的就是SQL语句中values括号里的所有内容
    vector<string> valueList = stringProcessor::Split(value, ",");
    return api->insertValue(tableName, valueList);
}

bool callAPI::callCreateTableAPI(const string& table, string& element){
    //目前还是测试接口有没有通
    // cout<<table<<endl;
    // cout<<element<<endl;
    stringProcessor::preTrim(element);
    vector<string> temp = stringProcessor::Split(element, ",");
    auto* attribution = new vector<dataType*>;
    dataType * tempAttr;
    int tempType, tempN;
    string tempName;
    bool tempUnique = false, tempPrimary = false, tempIndex = false;
    string primaryKey;
    int primaryKeyCount = 0;
    for(auto & i : temp)
    {
        vector<string> attr = stringProcessor::Split(i, " ");
        int size = attr.size();
        if(size >= 4 || size <= 1){
            cout<<"Syntax error! Can't create table! Illegal create command!"<<endl;
            return false;
        }
        // 第一种语法是primary key(xxx)
        if(attr[0] == "primary"){
            if(size != 2){
                cout<<"Syntax error! Can't create table! Illegal create command!"<<endl;
                return false;
            }
            int head = attr[1].find_first_of('(');
            int tail = attr[1].find_last_of(')');
            if (head == -1 || tail == -1){
                cout<<"Syntax error! Can't create table! Illegal create command!"<<endl;
                return false;
            }
            if (attr[1].substr(0, head) != "key"){
                cout<<"Syntax error! Can't create table! Illegal create command!"<<endl;
                return false;
            }
            primaryKey = attr[1].substr(head + 1, tail - head - 1);
            stringProcessor::preTrim(primaryKey);
            primaryKeyCount++;
            continue;
        }
        // 第二类 unique 类型,必须是3个单词，且最后一个是unqiue
        if(size == 3){
            if(attr[size-1] != "unique"){
                cout<<"Syntax error! Can't create table! Illegal create command!"<<endl;
                return false;
            }
            else
                tempUnique = true;
        }
        else tempUnique = false;

        // 第三类是普通的属性名+类型
        stringProcessor::preTrim(attr[0]);
        stringProcessor::preTrim(attr[1]);
        tempName = attr[0];
        int head, tail;
        head = attr[1].find_first_of('(');
        if(head == -1){
            string type = attr[1];
            if(type == "int")
                tempType = miniSQL_INT;
            else if(type == "float")
                tempType = miniSQL_FLOAT;
            else{
                cout<<"Syntax error! Can't create table! Illegal create command!"<<endl;
                return false;
            }
            tempN = 0;
        }
        else{
            string type = attr[1].substr(0, head);
            if(type != "char"){
                cout<<"Syntax error! Can't create table! Illegal create command!"<<endl;
                return false;
            }
            tempType = miniSQL_CHAR;
            tail = attr[1].find_last_of(')');
            if(tail == -1){
                cout<<"Syntax error! Can't create table! Illegal create command!"<<endl;
                return false;
            }
            type = attr[1].substr(head + 1, tail - head - 1);
            stringProcessor::preTrim(type);
            pair<bool, int> check = stringProcessor::intCheckAndChange(type);
            if(!check.first){
                cout<<"Syntax error! Can't create table! Illegal create command!"<<endl;
                return false;
            }
            tempN = check.second;
        }
        tempAttr = new dataType(tempType, tempN, tempName, tempUnique, tempPrimary, tempIndex);
        attribution->push_back(tempAttr);

    }
    // 两个简单的错误检查
    if(attribution->empty()){
        cout<<"Syntax error! Can't create table! No defined attribution!"<<endl;
        return false;
    }
    if(primaryKeyCount >= 2){
        cout<<"Syntax error! Can't create table! More than 1 primary keys!"<<endl;
        return false;
    }
    if(primaryKeyCount == 0){
        cout<<"Syntax error! Can't create table! No primary keys!"<<endl;
        return false;
    }
    int i;
    (*attribution)[0]->showDataType();
    for(i = 0; i < attribution->size(); i++){
        if((*attribution)[i]->typeName == primaryKey){
            (*attribution)[i]->isPrimaryKey = true;
            break;
        }
    }
    // (*attribution)[0]->showDataType();
    if( i == attribution->size()){
        cout<<"Syntax error! Can't create table! No matching primary key!"<<endl;
        return false;
    }
    bool result = api->createTable(table, attribution);
    delete attribution;
    return result;
}


// 调用delete API的静态成员函数，condition是where后面的全部内容
// 1表示成功，0表示失败，-1表示异常
int callAPI::callDeleteAPI(string& tableName, string& condition){
    //cout<<table<<endl;
    //cout<<condition<<endl;
    // 先去掉空格
    stringProcessor::preTrim(tableName);
    stringProcessor::preTrim(condition);
    cout<<tableName<<endl;
    cout<<condition<<endl;
    // 条件为空则不能删除，返回0表示失败
    if(condition.empty()){
        return 0;
    }
    Table* table = api->getTable(tableName);
    if(table == nullptr)
        return -1;
    vector<dataType*>* attribution = table->tableAttribution;
    auto* logicCondition = new vector<logicCompare>;
    vector<string> singleCondition = stringProcessor::Split(condition, "and");
    logicCompare* t;
    // 关于and进行切分之后再对每一个条件子句进行逻辑分析
    for(auto & i : singleCondition)
    {
        int logicType = stringProcessor::getCompareType(i);
        if(logicType == -1)
            return -1;
        t = stringProcessor::getLogic(i, logicType, attribution);
        if(t == nullptr){
            cout<<"Run time error! Illegal logic expression!"<<endl;
            delete logicCondition;
            return -1;
        }
        logicCondition->push_back(*t);
        delete t;
    }

    return api->deleteValue(tableName, logicCondition);
}

vector<vector<tableValue>*>* callAPI::callSelectAPI(string& tableName, string& condition){
    stringProcessor::preTrim(tableName);
    stringProcessor::preTrim(condition);
    // cout<<table<<endl;
    // cout<<condition<<endl;
    Table* table = api->getTable(tableName);
    if(table == nullptr){
        cout<<"Run time error! Don't find such table!"<<endl;
        return nullptr;
    }
    auto* attribution = table->tableAttribution;
    auto* logicCondition = new vector<logicCompare>;
    // 如果条件非空则需要进行子句的分割
    if(!condition.empty())
    {
        if(condition.find(" or ")!=condition.npos) {
            vector<string> temp = stringProcessor::Split(condition, " or ");
            logicCompare* t;
            int i;
            for(i = 0; i < temp.size(); i++){
                int type = stringProcessor::getCompareType(temp[i]);
                if(type == -1){
                    cout<<"Syntax error! Illegal data type!"<<endl;
                    return nullptr;
                }
                t = stringProcessor::getLogic(temp[i], type, attribution);
                if(t == nullptr)
                    return nullptr;
                logicCondition->push_back(*t);
                delete t;
            }
            vector<vector<tableValue>*>* result = api->select(tableName, logicCondition, 1);
            delete logicCondition;
            return result;
        }
        vector<string> temp = stringProcessor::Split(condition, "and");
        logicCompare* t;
        int i;
        for(i = 0; i < temp.size(); i++){
            int type = stringProcessor::getCompareType(temp[i]);
            if(type == -1){
                cout<<"Syntax error! Illegal data type!"<<endl;
                return nullptr;
            }
            t = stringProcessor::getLogic(temp[i], type, attribution);
            if(t == nullptr)
                return nullptr;
            logicCondition->push_back(*t);
            delete t;
        }
    }
    vector<vector<tableValue>*>* result = api->select(tableName, logicCondition);
    delete logicCondition;
    return result;
}