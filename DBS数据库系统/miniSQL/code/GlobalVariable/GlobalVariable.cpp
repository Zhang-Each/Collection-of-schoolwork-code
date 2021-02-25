//
// Created by 74096 on 2020/5/31.
//

#include"GlobalVariable.h"

string logicCompare::getValueName()
{
    return valName;
}

tableValue logicCompare::getImmediate()
{
    return immediate;
}

logicCompare::logicCompare(string &name, int op, tableValue imm)
{
    valName = name;
    operation = op;
    immediate = imm;
}

int logicCompare::compareInt(int a, int b)
{
    if(a > b)
        return GREATER;
    else if(a < b)
        return LESS;
    else
        return EQUAL;
}

int logicCompare::compareFloat(float a, float b)
{
    if(a > b)
        return GREATER;
    else if(a < b)
        return LESS;
    else
        return EQUAL;
}

int logicCompare::compareChar(const char *a, const char *b, int length)
{
    int len;
    if (strlen(a)< strlen(b)) len=strlen(b);
    else len= strlen(a);
    if(len>length) len=length;
    for(int i = 0; i < len; i ++){
        if(a[i] == '\n' && b[i] == '\n')
            return EQUAL;
        else if(a[i] == '\n' && b[i] != '\n')
            return LESS;
        else if(a[i] != '\n' && b[i] == '\n')
            return GREATER;
        else{
            if(a[i] > b[i])
                return GREATER;
            else if(a[i] < b[i])
                return LESS;
        }
    }
    return EQUAL;
}

bool logicCompare::checkCondition(int result)
{
    switch (operation)
    {
        case EQUAL :
            if (result != EQUAL)
                return false;
            return true;
        case NOTEQUAL:
            if (result == EQUAL)
                return false;
            return true;
        case GREATER:
            if (result != GREATER)
                return false;
            return true;
        case LESS:
            if (result != LESS)
                return false;
            return true;
        case GREATEREQUAL:
            if (result == LESS)
                return false;
            return true;
        case LESSEQUAL:
            if (result == GREATER)
                return false;
            return true;
    }
    return false;
}