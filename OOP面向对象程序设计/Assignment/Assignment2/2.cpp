#include<iostream>
#include<string>
#include<map>
#include<vector>
using namespace std;

#define MAX_SIZE 1000;
map<string,int> course;
map<string,int> student;
int Number_student=0;

//a function to check the map
void showMap(map<string,int> m);
//show the average,min,max of the grades course by course
void showResult(vector<vector<int>> info,vector<string> s1,vector<string> s2,double ave[]);
//show the grades of students
void showStatic(double s[],int a[],int b[],int n);

int main()
{
    //step 1:record the names of course_name
    //store the names of course in the map
    vector<string> course_name_vec,stu_name;
    int i,j,Number_course;
    cout<<"Please input the total number of different courses:"<<endl;
    cin>>Number_course;
    cout<<"Please input the name of the course each per line:"<<endl;
    for(i=0;i<Number_course;i++){
        string course_name;
        cin>>course_name;
        course[course_name]=i;
        course_name_vec.push_back(course_name);
    }

    //2 vectors to store the grades
    vector<int> temp;
    vector<vector<int>> info;
    for(i=0;i<Number_course;i++){
        temp.push_back(-1);
    }
    //showMap(course); call the function when you want to debug

    string name,course_name;
    int score;
    
    cout<<"Then input the name course and score of students, each record pre line"<<endl;
    cout<<"Input 'end' if you finish the input"<<endl;
    while(cin>>name){
        if(name=="end"){
            break;
        }
        else{
            cin>>course_name>>score;
            //if the student is not in the map
            //add him in the map and the vector info
            if(student.count(name)==0){
                student[name]=Number_student++;
                info.push_back(temp);
                stu_name.push_back(name);
            }
            info[student[name]][course[course_name]]=score;
        }
    }
    //showStudent(info);
    //define and init the arrays
    double *average_stu=new double[Number_student];
    double *average_total=new double[Number_course];
    int *min=new int[Number_course],*max=new int[Number_course];
    for(i=0;i<Number_course;i++){
        min[i]=5;
        max[i]=0;
        average_total[i]=0.0;
    }
    //compute every one's average score of course
    for(i=0;i<info.size();i++){
        int count=0;//the number of courses that have scores
        for(j=0;j<info[i].size();j++){
            if(info[i][j]!=-1){
                average_stu[i]+=info[i][j];
                count++;
            }
        }
        average_stu[i]=average_stu[i]*1.0/(count*1.0);
    }

    //compute the min,max,average of each course
    for(j=0;j<Number_course;j++){
        int count=0;
        for(i=0;i<info.size();i++){
            if(info[i][j]>=0){
                count++;
                average_total[j]+=info[i][j];
                if(info[i][j]<min[j])
                    min[j]=info[i][j];
                if(info[i][j]>max[j])
                    max[j]=info[i][j];
            }
        }
        average_total[j]=1.0*average_total[j]/count;
    }

    //print the result

    //print the title
    cout<<"------------Student Info--------------"<<endl;
    //print the info of each student
    showResult(info,course_name_vec,stu_name,average_stu);
    //print out the average,min and max grade of each class
    showStatic(average_total,min,max,Number_course);
    
    system("pause");
    return 0;

}


//a test function could be used to show the map of students or courses
void showMap(map<string,int> m)
{
    //use a iterator to show the course
    map<string,int>::iterator i=m.begin();
    while(i!=m.end()){
        cout<<i->first<<"   "<<i->second<<endl;
        i++;
    }
}

//a test function that can be used to check a 2-dimension vector
void showStudent(vector<vector<int>> s)
{
    int i,j;
    for(i=0;i<s.size();i++){
        for(j=0;j<s[i].size();j++){
            cout<<s[i][j]<<"\t";
        }
        cout<<endl;
    }
}

//show the average,min,max of the grades course by course
void showResult(vector<vector<int>> info,vector<string> s1,vector<string> s2,double ave[])
{
    int i,j;
    cout<<"no\t"<<"name\t";
    for(i=0;i<s1.size();i++){
        cout<<s1[i]<<'\t';
    }
    cout<<"average\t"<<endl;

    for(i=0;i<info.size();i++){
        cout<<i+1<<"\t"<<s2[i]<<'\t';
        for(j=0;j<info[i].size();j++){
            if(info[i][j]==-1)
                cout<<"--\t";
            else
                cout<<info[i][j]<<"\t";
        }
        cout<<ave[i]<<"\t"<<endl;
    }
}

//show the grades of students
void showStatic(double s[],int a[],int b[],int n)
{
    int i;
    cout<<"\t"<<"average\t";
    for(i=0;i<n;i++){
        cout<<s[i]<<"\t";
    }
    cout<<endl;
    cout<<"\t"<<"min\t";
    for(i=0;i<n;i++){
        cout<<a[i]<<"\t";
    }
    cout<<endl;
    cout<<"\t"<<"max\t";
    for(i=0;i<n;i++){
        cout<<b[i]<<"\t";
    }
    cout<<endl;
}