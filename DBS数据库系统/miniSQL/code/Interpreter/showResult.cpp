//
// Created by 74096 on 2020/6/15.
//

#include "showResult.h"
void showResult::showDropTable(bool flag, const string& table){
    if(flag){
        cout<<"Drop Table "<<table<<" Successfully!"<<endl;
    }
    else{
        cout<<"Failed in dropping table "<<table<<". Please try again!"<<endl;
    }
}
void showResult::showDropIndex(bool flag, const string& index){
    if(flag){
        cout<<"Drop Index "<<index<<" Successfully!"<<endl;
    }
    else{
        cout<<"Failed in dropping index "<<index<<". Please try again!"<<endl;
    }
}
void showResult::showCreateTable(bool flag, const string& table){
    if(flag){
        cout<<"Create Table "<<table<<" Successfully!"<<endl;
    }
    else{
        cout<<"Failed when creating table "<<table<<". Please try again!"<<endl;
    }
}
void showResult::showCreateIndex(bool flag, const string& index){
    if(flag){
        cout<<"Create Index on "<<index<<" Successfully!"<<endl;
    }
    else{
        cout<<"Failed when creating table "<<index<<". Please try again!"<<endl;
    }
}
void showResult::showInsert(bool flag, const string& table){
    if(flag){
        cout<<"Insert into table "<<table<<" Successfully!"<<endl;
    }
    else{
        cout<<"Insertion failed! Please try again!"<<endl;
    }
}
void showResult::showDelete(int flag, const string& table){
    if(flag == 1){
        cout<<"Delete from table "<<table<<" Successfully!"<<endl;
    }
    else if(!flag){
        cout<<"Deletion failed! Please try again!"<<endl;
    }
    else{
        cout<<"Run time error! Table doesn't exist!"<<endl;
    }
}


void showResult::showSelect(vector<vector<tableValue>*>* result, string tableName){
    //待完成，需要展示select到的结果
    //经过测试，接口已经调通了
//    cout<<"---------Selected Results----------"<<endl;
    if(result == nullptr){
        cout<<"No selected result at all!"<<endl;
        return;
    }
    Table* table = api->getTable(tableName);
    vector<dataType*>* attribution = table->tableAttribution;
    vector<tableValue>* tempLine;
    dataType* temp;
    int i, j, totalLength = 1, size = attribution->size();
    for(i = 0; i < size; i++){
        temp = (*attribution)[i];
        if(temp->type == miniSQL_CHAR)
            totalLength += temp->getDataLength() + 1;
        else
            totalLength += int(temp->typeName.size()) + 10 + 1;
    }
    cout << beautify(totalLength, "-") << endl;
    // 打印第一行属性栏
    cout << "|";
    for(i = 0; i < size; i++){
        int len;
        temp = (*attribution)[i];
        if(temp->type == miniSQL_CHAR)
            len = temp->getDataLength();
        else len = temp->typeName.size() + 10;
        len -= temp->typeName.size();
        cout << temp->typeName << beautify(len) << "|";
    }
    cout<<endl;
    cout << beautify(totalLength, "-") << endl;
    // 打印后面的每一档
    for(i = 0; i < result->size(); i++)
    {
        tempLine = (*result)[i];
        cout << "|";
        for(j = 0; j < size; j++)
        {
            temp = (*attribution)[j];
            int len;
            if (temp->type == miniSQL_CHAR)
                len = temp->getDataLength();
            else
                len = temp->typeName.size() + 10;
            if(temp->type == miniSQL_INT) {
                len -= to_string((*tempLine)[j].INT).size();
                cout << (*tempLine)[j].INT << beautify(len) << "|";
            }
            else if(temp->type == miniSQL_FLOAT) {
                string str = to_string((*tempLine)[j].FLOAT);
                int k = (int)str.size();
                string::size_type pos = str.find('.');
                if(pos == str.npos){
                    int num=(int)(*tempLine)[j].FLOAT;
                    len -= str.size();
                }
                else {
                    for(; k > 0; k--) {
                        if(str[k] == '0') str.erase(k, 1);
                        if(k == pos + 2) break;
                    }
                    len -= str.size() - 1;
                }
                cout << (*tempLine)[j].FLOAT << beautify(len) << "|";
            }
            else {
                len -= strlen((*tempLine)[j].CHAR);
                cout << (*tempLine)[j].CHAR << beautify(len) << "|";
            }
        }
        cout<<endl;
        cout << beautify(totalLength, "-") << endl;
    }
    cout<<""<<endl;
}

string showResult::beautify(int length, string op)
{
    string result;
    int i;
    for(i = 0; i < length; i++) result += op;
    return result;
}
