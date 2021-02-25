#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<queue>
#include<algorithm>

using namespace std;

//The function to check whether some of the code become prefix of others
bool check_prefix(vector<string> code);
//The function to calculate the smallest sum of weight in the Huffman tree
int calculate_weight(priority_queue<int,vector<int>,greater<int>>& huffman_tree);

int main()
{
    //some basic variables in the program
    int i,j,n,m,fluquency;
    char character;
    //using STL in C++ to build a min-heap for the huffman tree
    priority_queue<int,vector<int>,greater<int>> huffman_tree;
    //a map to store the weight of each character
    map<char,int> huffman_code;
    //store the result of each group of the input huffman code
    vector<int> result;
    //read in the fluquency of each character
    cin>>n;
    for(i=0;i<n;i++)
    {
        cin>>character>>fluquency;
        huffman_code[character]=fluquency;
        //build a min-heap as huffman tree
        huffman_tree.push(fluquency);
    }
    //calculate the total weight of the huffman tree
    int total_weight=calculate_weight(huffman_tree);
    // cout<<total_weight<<endl;
    //check each group of the huffman code
    cin>>m;
    for(i=0;i<m;i++)
    {
        map<char,string> temp;
        vector<string> code;
        char x;
        string y;
        int temp_weight=0;
        //read in the characters and calculate the total weight
        for(j=0;j<n;j++)
        {
            cin>>x>>y;
            code.push_back(y);
            temp_weight+=huffman_code[x]*y.length();
        }

        //a correct group of huffman code should satisfy the 2 conditions
        //1. the total weight is equal to the smallest weight
        //2. none of the huffuman code is others' prefix  
        if(temp_weight==total_weight&&check_prefix(code))
        {
            result.push_back(1);
        }
        else{
            result.push_back(0);
        }
    }
    //output the result: Yes or No
    for(i=0;i<result.size();i++)
    {
        if(result[i])
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;
    }
    system("pause");
    return 0;
}

//an algorithm to check if exist prefix
bool check_prefix(vector<string> code)
{
    //sort the code in a increasing order
    sort(code.begin(), code.end());
    int i,j;
    //check each huffman code whether is is others' prefix or not
    //It need O(N^2) time complexity
    for(i=0;i<code.size();i++)
    {
        int len=code[i].size();
        for(j=i+1;j<code.size();j++)
        {
            //get the substring of the first len characters of the huffman code
            string sub_prefix=code[j].substr(0,len);
            //check whether they are the same
            if(sub_prefix==code[i])
            {
                return false;
            }
        }
    }
    return true;
}

// calculate the total weight of the huffuman tree
// the result is also a smallest weight
int calculate_weight(priority_queue<int,vector<int>,greater<int>>& huffman_tree)
{
    int result=0;
    while(true)
    {
        //using a greedy method to calculate the total weight of Huffman tree
        int weight=huffman_tree.top();
        huffman_tree.pop();
        if(huffman_tree.size()==0){
            break;
        }
        //simulation the merge of the 2 smallest nodes in the huffuman tree
        weight+=huffman_tree.top();
        huffman_tree.pop();
        huffman_tree.push(weight);
        result+=weight;
    }
    return result;
}