#include<iostream>
#include <cstring>
#include<algorithm>

using namespace std;

typedef struct node
{
       char name;
       int weight, parent;
       int lchild, rchild;
       node():name(), weight(0), parent(0), lchild(0),rchild(0){}
}HTNode,*HuffmanTree;

typedef char **HuffmanCode;
typedef struct
{
       int weight, locate;
}TNode,*Temp;

void CreatHuffmanTree(HuffmanTree &HT, int n);
void CreatHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n, int m);
int main()
{
       HuffmanTree HT;
       HuffmanCode HC;
       char p = 'y';
       int t,n;
       while (p=='y')
       {
              cout << "Please enter the number of characters :";
              cin >> n;
              CreatHuffmanTree(HT, n);
              cout << "Please enter the number of test cases :";
              cin >> t;
              for(int m = 0; m < t; m++)
                     CreatHuffmanCode(HT, HC, n , m);
              cout << "input again: y, quit: n" << endl;
              cin >> p;
       }
       system("pause");
       return 0;
}

bool compare(const TNode &x, const TNode &y) {

	return x.weight < y.weight;
}
//Generate Huffman Tree
void CreatHuffmanTree(HuffmanTree &HT, int n)
{
       int i, j, k, s1, s2, num;
       HT = new HTNode[2 * n];
       cout << "Enter the frequency of characters in format(character frequency):"<<endl;
       for (i = 1; i <= n; i++)
       {
              cin >> HT[i].name >> HT[i].weight;
       }
       
       for (i = n + 1; i < 2 * n; i++)
       {
              /*Select the subscripts of the two nodes whose parent 
              is 0 and the weight is the smallest from 1 ~ i-1, and
              count the number of nodes whose parents are 0 in 1 ~ i-1*/
              num = 0;
              for (k = 1; k < i; k++)
              {
                     if (HT[k].parent == 0)
                     {
                            num++;
                     }
              }
              Temp T;
              T = new TNode[num];
              for (j = 0, k = 1; k < i; k++)
              {
                     if (HT[k].parent == 0)
                     {
                            T[j].weight = HT[k].weight;
                            T[j].locate = k;
                            j++;
                     }
              }
              //sort
              sort(T,T+num,compare);
              s1 = T[0].locate;
              s2 = T[1].locate;
              HT[s1].parent = i;
              HT[s2].parent = i;
              HT[i].lchild = s1;
              HT[i].rchild = s2;
              HT[i].weight = HT[s1].weight + HT[s2].weight;
              delete T;
       }
}
//Create Huffman Code
void CreatHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n ,int m)
{
       int i, c, f,start;
       char *cd;
       HC = new char*[n + 1];
       cd = new char[n];
       cd[n - 1] = '\0';
       for (i = 1; i <= n; i++)
       {
              start = n - 1;
              c = i;
              f = HT[i].parent;
              while (f != 0)
              {
                     start--;
                     if (HT[f].lchild == c)
                     {
                            cd[start] = (m % 2)?'0':'1';
                     }
                     else
                     {
                            cd[start] = (m % 3)?'1':'0';
                     }
                     c = f;
                     f = HT[f].parent;
              }
              HC[i] = new char[n - start];
              strcpy(HC[i], &cd[start]);
       }
       delete cd;
       cout << "Haffman code:";
       for (i = 1; i <= n; i++)
       {
              cout << HT[i].name<<" "<< HC[i] << endl;
       }
       cout << endl;
}