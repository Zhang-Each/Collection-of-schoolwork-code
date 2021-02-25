#include<stdio.h>
int s[10010]={-1};
void Set(int s[],int root1,int root2);
int Find(int x,int s[]);
int main()
{
    int n,count=0;
    scanf("%d", &n);
    char x;
    scanf("%c", &x);
    while(x!='S'){
        int a,b;
        scanf("%d %d",&a,&b);
        if(x=='I'){
            Set(s,a,b);
        }
        else if(x=='C'){
            if(Find(a,s)==Find(b,s)) {
                printf("yes\n");
            }
            else{
                printf("no\n");
            }
        }
        scanf("%c",&x);
    }
    for(int i=1;i<=n;i++){
        if(s[i]<=0) count++;
    }
    if(count==1){
        printf("The network is connected.");
    }
    else{
        printf("There are %d components.",count);
    }
    return 0;
}

void Set(int s[],int root1,int root2)
{
    if(s[root2]<s[root1]){
        s[root2]+=s[root1];
        s[root1]=root2;
    }
    else {
        s[root1]+=s[root2];
        s[root2]=root1;
    }
}

int Find(int x,int s[])
{
    if(s[x]<=0){
        return x;
    }
    else{
        return s[x]=Find(s[x],s);
    }
}