#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>
using namespace std;

//author:Zhang Yichi ID:3180103772
//E-mail: 3180103772@zju.edu.cn

int main()
{
    //some basic arrays, this time I will not use a 'class' because it hasn't been taught
    //I think the names of the variables are not difficult to understand
    string name[10];
    cout << name[0];
    int i, j, score1[10], score2[10], score3[10], maxscore[3], minscore[3];
    double average[10], average_score1 = 0, average_score2 = 0, average_score3 = 0;
    //init the maxscore and minscore
    for (i = 0; i < 3; i++)
    {
        maxscore[i] = 0;
        minscore[i] = 5;
    }
    //first read in 10 records of student information
    for (i = 0; i < 10; i++)
    {
        cin >> name[i] >> score1[i] >> score2[i] >> score3[i];
        //calculate the average scores
        average[i] = (double)(score1[i] + score2[i] + score3[i]) / 3.0;
        average_score1 += score1[i];
        average_score2 += score2[i];
        average_score3 += score3[i];
        //update the max and min scores
        if (maxscore[0] < score1[i])
        {
            maxscore[0] = score1[i];
        }
        if (maxscore[1] < score2[i])
        {
            maxscore[1] = score2[i];
        }
        if (maxscore[2] < score3[i])
        {
            maxscore[2] = score3[i];
        }
        if (minscore[0] > score1[i])
        {
            minscore[0] = score1[i];
        }
        if (minscore[1] > score2[i])
        {
            minscore[1] = score2[i];
        }
        if (minscore[2] > score3[i])
        {
            minscore[2] = score3[i];
        }
    }

    //calculate the average scores
    average_score1 /= 10.0;
    average_score2 /= 10.0;
    average_score3 /= 10.0;

    //here is another way to make tha output aligned
    /*
    for(i=0;i<10;i++){
        int space=8-name[i].length();
        if(i!=9){
            name[i]="       "+name[i];
        }
        else{
            name[i]="      "+name[i];
        }
        for(j=0;j<space;j++){
            name[i]+=" ";
        }
    }
    */

    //print the result
    cout << "no      name    score1  score2  score3  average" << endl;
    for (i = 0; i < 10; i++)
    {
        cout << setiosflags(ios::left) << setw(8) << i + 1 << setw(8) << name[i]; //use left aligned
        cout << setiosflags(ios::left) << setw(8) << score1[i] << setw(8) << score2[i] << setw(8) << score3[i];
        if (floor(average[i]) == average[i])
        {
            cout << (int)average[i] << endl;
        }
        else
        {
            cout << setprecision(6) << average[i] << endl;
        }
    }

    //output the average score ,the min score and the max score
    cout << "        average ";
    cout << setiosflags(ios::left) << setw(8) << setprecision(2) << average_score1 << setw(8) << setprecision(2) << average_score2 << setw(8) << setprecision(2) << average_score3;
    cout << endl;
    cout << "        min     ";
    cout << setiosflags(ios::left) << setw(8) << minscore[0] << setw(8) << minscore[1] << setw(8) << minscore[2];
    cout << endl;
    cout << "        min     ";
    cout << setiosflags(ios::left) << setw(8) << maxscore[0] << setw(8) << maxscore[1] << setw(8) << maxscore[2];
    cout << endl;
    system("pause");
    return 0;
}