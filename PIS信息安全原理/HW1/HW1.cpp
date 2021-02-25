#include<iostream>
#include<string>
#include<vector>
using namespace std;

//author:zhangyichi-3180103772
string CreateKey(int n);
int checkplain(string s);
int f(string s,int i);
void OutPutCode(vector<int> s);

int main()
{
    int i;
    string plain,key;

    cout<<"Please Input the plain in a line:"<<endl;
    cin>>plain;
    if(!checkplain(plain)){
        cout<<"Invalid Input!"<<endl;
        return 0;
    }
    key=CreateKey(plain.size());

    //Encryption 
    vector<int> cipher1,cipher;
    //step1:change to ASCII code
    for(i=0;i<plain.size();i++){
        int unit;
        if(plain[i]>='0' && plain[i]<='9'){
            unit=plain[i]-'0'+key[i]-'0';
        }
        else if(plain[i]>='A' && plain[i]<='Z'){
            unit=plain[i]-'A'+65+key[i]-'0';
        }
        else if(plain[i]>='a' && plain[i]<='z'){
            unit=plain[i]-'a'+97+key[i]-'0';
        }
        unit*=f(key,i);
        cipher1.push_back(unit);
    }

    //OutPutCode(cipher1);
    //step 2: a swap of each 3
    for(i=0;i<=cipher1.size()-3;i+=3){
        int t=cipher1[i];
        cipher1[i]=cipher1[i+1];
        cipher1[i+1]=cipher1[i+2];
        cipher1[i+2]=t;
    }

    
    //OutPutCode(cipher1);

    //step 3: reverse
    for(i=0;i<cipher1.size();i++){
        cipher.push_back(cipher1[cipher1.size()-i-1]);
    }
    //step 4:show the final cipher
    cout<<"The Ciphertext is:"<<endl;
    OutPutCode(cipher);
    
    //Decryption
    vector<int> cipher2;
    string origin;
    for(i=0;i<cipher.size();i++){
        cipher2.push_back(cipher[cipher1.size()-i-1]);
    }
    for(i=0;i<=cipher2.size()-3;i+=3){
        int t=cipher2[i+2];
        cipher2[i+2]=cipher2[i+1];
        cipher2[i+1]=cipher2[i];
        cipher2[i]=t;
    }
    
    for(i=0;i<cipher2.size();i++){
        cipher2[i]/=f(key,i);
        cipher2[i]-=(key[i]-'0');
        if(cipher2[i]>=0&&cipher2[i]<=9){
            origin+='0'+cipher2[i];
        }
        else if(cipher2[i]>=65&&cipher2[i]<=90){
            origin+='A'+cipher2[i]-65;
        }
        else if(cipher2[i]>=97&&cipher2[i]<=122){
            origin+='a'+cipher2[i]-97;
        }
    }
    cout<<"The result of decryption is:\n";
    cout<<origin<<endl;
    system("pause");
    return 0;
}


int checkplain(string s)
{
    for(int i=0; i<s.length();i++){
        int x,y,z;
        x=(s[i]>='0' && s[i]<='9');
        y=(s[i]>='A' && s[i]<='Z');
        z=(s[i]>='a' && s[i]<='z');
        if(!(x==1||y==1||z==1)){
            return 0;  
        }
    }
    return 1;
}

string CreateKey(int n)
{
    string result;
    for(int i=0;i<n;i++){
        if(i%10==0||i%10==6){
            result+='3';
        }
        else if(i%10==1||i%10==4){
            result+='1';
        }
        else if(i%10==2){
            result+='8';
        }
        else if(i%10==3||i%10==5){
            result+='0';
        }
        else if(i%10==7||i%10==8){
            result+='7';
        }
        else if(i%10==9){
            result+='2';
        }
    }
    return result;
}

void OutPutCode(vector<int> s)
{
    for(int i=0;i<s.size();i++){
        if(i==0){
            cout<<s[i];
        }
        else{
            cout<<" "<<s[i];
        }
    }
    cout<<endl;
}

int f(string s,int i)
{
    return 3429-(s[i]-'0');
}