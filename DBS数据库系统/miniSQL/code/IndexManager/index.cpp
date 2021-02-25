//
// Created by 74096 on 2020/6/5.
//

#include "index.h"
index::index(string& self, string& table, string& column)
{
    name = self;
    tableName = table;
    columnName = column;
}


string index::getName() const
{
    return name;
}


string index::getTableName() const
{
    return tableName;
}

string index::getColumnName() const
{
    return columnName;
}