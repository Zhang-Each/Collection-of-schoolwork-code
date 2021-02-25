//
// Created by 74096 on 2020/6/5.
//

#ifndef CODE_INDEX_H
#define CODE_INDEX_H
#include<string>

using namespace std;

class index {
public:
    index(string& self, string& table, string& column);
    string getName() const;
    string getTableName() const;
    string getColumnName() const;

private:
    string name, tableName, columnName;
};


#endif //CODE_INDEX_H
