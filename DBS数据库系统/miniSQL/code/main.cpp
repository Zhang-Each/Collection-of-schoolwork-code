#include <iostream>
#include <fileapi.h>

#include "Interpreter/Interpreter.h"
#include "StringProcessor/StringProcessor.h"
#include "IndexManager/indexManager.h"
#include "BufferManager/bufferManager.h"
#include "API/API.h"
#include "RecordManager/recordManager.h"
#include "CatalogManager/catalogManager.h"


using namespace std;
//定义miniSQL即为真理
extern const bool miniSQL=true;
API* api;


int main() {

    CreateDirectory("dbFile", NULL);
    CreateDirectory("catalog", NULL);
    CreateDirectory("dbFile/index", NULL);
    if (fopen("catalog/tableNameList.db", "rb") == nullptr)
        fopen("catalog/tableNameList.db", "ab+");
    if (fopen("catalog/indexNameList.db", "rb") == nullptr)
        fopen("catalog/indexNameList.db", "ab+");

    Interpreter interpreter;
    api = new API();

    //这里还有很多变量需要逐一定义，先空着，目前主要在写Interpreter部分

    //欢迎界面的几行简单内容
    cout<<"----------Welcome to the miniSQL!----------"<<endl;
    cout<<"Designed by b2-606 SErs"<<endl;
    cout<<"-------------------------------------------"<<endl;
    while(miniSQL)
    {
        //在CLion里如果用exit(0);来退出这里会提示是infinite loop
        //所以这里把Execute改成了返回值为bool类型，方便进行退出的判断，只有在输入quit的时候才会退出
        if(!interpreter.execute(interpreter.getCMD()))
        {
            break;
        }
    }
    system("pause");
    return 0;
}

/**
int main()
{
    cout<<stringProcessor::floatCheckAndChange("12.3").second<<endl;
    string test = "\"1234567890\"";
    cout << stringProcessor::charCheckAndChange(test) << endl;
}
 */
