//
// Created by 74096 on 2020/5/24.
//

#include "Interpreter.h"

string Interpreter::getCMD()
{
    //这一段主要是从命令行读取一条完整的指令
    string cmd,temp;
    int flag = false;
    while(true) {
        if(!flag) {
            cout<<"miniSQL";
            flag = true;
        }
        else
            cout<<"       ";
        cout<<">";
        getline(cin,temp);
        stringProcessor::preTrim(temp);
        if(temp.empty())
            continue;
        cmd += temp;
        if(temp[temp.length()-1] == ';')
            break;
    }
    return stringProcessor::cmdOptimum(cmd);
}

//这个函数的返回值其实是表示可以继续下一句SQL指令的读取和执行，不是说语法是否错误
//这里就算语法错误返回的也是true，因为要执行下一句，只有当需要退出的时候才会返回false，我暂时也想不出更好的设计了
bool Interpreter::execute(std::string cmd)
{
    //execute the cmd in a string
    //cout<<cmd<<endl;
    //退出的情况
    if(cmd.find("quit") == 0) {
        if(cmd.length() != 4) {
            cout<<"Syntax Error!Please try again!"<<endl;
            return true;
        }
        else {
            cout<<"Thank you for using such a sb system, see you next time!"<<endl;
            cout<<"-------------------------------------------"<<endl;
            //exit(0);
            return false;
        }
    }
    else if(cmd.find("execfile") == 0) {
        string file_name = cmd.substr(8);
        stringProcessor::preTrim(file_name);
        // cout<<"file name: "<<file_name<<endl;
        //这里需要转换一下文件的路径，默认这个SQL文件是放在code文件夹下的，输入的时候输入的是文件名，不包含路径
        string path = "..\\" + file_name;
        // cout<<"file path: "<<path<<endl;
        exeFile(path);
        return true;
    }
    //此处可以添加一个能彻底去掉多余空格的处理函数，不过我这里先做最理想的情况就是每个刚好一个空格
    else //下面都是基本的SQL语句的语法分解
    {
        int checkBracket = stringProcessor::bracketProcessor(cmd);
        if(!checkBracket)
            cout<<"Syntax Error! Please check your brackets in the SQL!"<<endl;
        else if(checkBracket == 1) {
            //对create和insert语句进行初步的语义分割
            //cout<<cmd<<endl;
            int start = cmd.find_first_of('(');
            int end = cmd.find_last_of(')');
            //Kind 和 Val分别代表了进行的操作和表名，需要操作的数据
            string operateKind = cmd.substr(0, start);
            string operateVal = cmd.substr(start + 1, end - start - 1);
            //cout<<operateKind<<endl;
            //cout<<operateVal<<endl;
            //继续进一步的处理
            vector<string> operate = stringProcessor::Split(operateKind, " ");
            operate.push_back(operateVal);
            stringProcessor::showOperation(operate);

            //正确的create table语句格式应该试
            //create table table_name ( attributions );
            //attributions 需要在后面进一步的分割
            //create table语句固定只能有4个参数
            if(operate[0] == "create") {
                if(operate[1] == "table") {
                    if(operate.size() >= 5) {
                        cout<<"Syntax Error! Extra parameters in create table"<<endl;
                        return true;
                    }
                    else {
                        //进行进一步的create table的语法分解
                        showResult::showCreateTable(callAPI::callCreateTableAPI(operate[2], operate[3]), operate[2]);
                        return true;
                    }
                }
                //create index index_name on table_name ( attribution_name );
                //operation里固定的只能有6个
                else if(operate[1] == "index") {
                    if(operate.size() >= 7) {
                        cout<<"Syntax Error! Extra parameters in create index!"<<endl;
                        return true;
                    }
                    else if(operate.size() <= 5) {
                        cout<<"Syntax Error! Lack of parameters in create index!"<<endl;
                        return true;
                    }
                    //接下来一定是有6个operate的create index语句
                    else if(operate[3] != "on") {
                        cout<<"Syntax Error! No such create index operation!"<<endl;
                        return true;
                    }
                    else {
                        cout<<"1"<<endl;
                        //进行create index的语法分解
                        showResult::showCreateIndex(callAPI::callCreateIndexAPI(operate[2], operate[4], operate[5]), operate[4]);
                        return true;
                    }
                }
            }
            //insert语句的格式为：insert into table_name values (xxx,xxx,xxx);
            //operate中固定为5个，其他都是语法错误
            else if(operate[0] == "insert") {
                if(operate[1] != "into") {
                    //不是into 语法错误
                    cout<<"Syntax Error! Insert Key Word Error!"<<endl;
                    return true;
                }
                else {
                    if(operate.size() > 5) {
                        cout<<"Syntax Error! Extra parameters in insert!"<<endl;
                        return true;
                    }
                    else if(operate.size() <= 4) {
                        cout<<"Syntax Error! Lack of parameters in insert."<<endl;
                        return true;
                    }
                    else if(operate[3] != "values") {
                        cout<<"Syntax Error! Key Word Error!"<<endl;
                        return true;
                    }
                    else {
                        //正常执行insert语句,语法分解
                        showResult::showInsert(callAPI::callInsertAPI(operate[2], operate[4]), operate[2]);
                        return true;
                    }
                }
            }
        }
        //这里涵盖的指令有drop，delete，select，
        else if(checkBracket == -1) {
            //对其他类型的语句进行初步语义分割
            vector<string> operate = stringProcessor::Split(cmd, " ");
            for(auto & i : operate) {
                //再一次去括号，防止有多余的括号
                stringProcessor::preTrim(i);
            }
            if(operate.empty()) {
                cout<<"Syntax Error! No executable SQL command!"<<endl;
                return true; //继续下一句SQL命令
            }
            stringProcessor::showOperation(operate);
            if(operate[0] == "drop")
            {
                //第一种drop语句：drop table xxx;
                if(operate[1] == "table")
                {
                    if(operate.size() != 3){
                        //参数个数错误
                        cout<<"Syntax Error! Extra parameters in drop table!"<<endl;
                        return true;
                    }
                    else{
                        //进行drop table的语法分解，并调用API
                        showResult::showDropTable(callAPI::callDropTableAPI(operate[2]), operate[2]);
                        return true;
                    }
                }
                //第二种drop index xxx;
                else if(operate[1] == "index")
                {
                    if(operate.size() != 3){
                        cout<<"Syntax Error! Extra parameters in drop index!"<<endl;
                        return true;
                    }
                    else{
                        //进行drop index的语法分解
                        showResult::showDropIndex(callAPI::callDropIndexAPI(operate[2]), operate[2]);
                        return true;
                    }
                }
                else{
                    //drop了table和index以外的东西
                    cout<<"Syntax Error! No such drop operation!"<<endl;
                    return true;
                }
            }
            //正常的delete语句应该是delete from table_name where xxx ;
            else if(operate[0] == "delete") {
                if(operate[1] != "from") {
                    cout<<"Syntax Error! No such delete operation!"<<endl;
                    return true;
                }
                else{
                    if(operate.size() <= 4) {
                        cout<<"Syntax Error! Lack of parameters."<<endl;
                        return true;
                    }

                    else if(operate[3] != "where") {
                        cout<<"Syntax Error! Key word Error!"<<endl;
                        return true;
                    }
                    else {
                        //正常执行delete语句的部分
                        //cout<<"Exe delete!"<<endl;
                        string condition = cmd.substr(cmd.find("where") + 5);
                        showResult::showDelete(callAPI::callDeleteAPI(operate[2], condition), operate[2]);
                        return true;
                    }
                }
            }

            //select语句的格式为select * from table_name where xxx;
            else if(operate[0] == "select"){
                if(operate.size() <= 3) {
                    cout<<"Syntax Error! Lack of parameters."<<endl;
                    return true;
                }
                else if(operate[1] != "*"){
                    cout<<"Syntax Error! No such select operation!"<<endl;
                    return true;
                }
                //没有附加条件的查询
                else if(operate.size() == 4){
                    if(operate[2] != "from"){
                        cout<<"Syntax Error! Key Word Error!"<<endl;
                        return true;
                    }
                    else{
                        //正常执行，无条件的查询语句
                        //这一部分比较难写，先空着
                        string condition = "";
                        showResult::showSelect(callAPI::callSelectAPI(operate[3], condition), operate[3]);
                        return true;
                    }
                }
                else if(operate[2] != "from" || operate[4] != "where"){
                    cout<<"Syntax Error! Key Word Error!"<<endl;
                    return true;
                }
                else {
                    //正常执行select语句的分割，有条件的查询语句
                    int where = cmd.find("where");
                    string condition = cmd.substr(where+5);
                    showResult::showSelect(callAPI::callSelectAPI(operate[3], condition), operate[3]);
                    return true;
                }
            }
        }


    }

    return true;
}

void Interpreter::exeFile(const string &file)
{
    ifstream fin;
    fin.open(file, ios::in);
    if(fin.fail()) {
        cout<<"Error! Can't find the file on the path! Please try again!"<<endl;
        return ;
    }
    else {
        string cmd,temp;
        while(getline(fin,temp)) {
            stringProcessor::preTrim(temp);
            if(temp.empty())
                continue;
            cmd += temp;
            if(temp[temp.length() - 1] == ';') {
                cmd = stringProcessor::cmdOptimum(cmd);
                execute(cmd);
                cmd = "";
            }
        }
        if(!cmd.empty()) {
            cout<<"Syntax Error! Please try again!"<<endl;
        }
    }
}
