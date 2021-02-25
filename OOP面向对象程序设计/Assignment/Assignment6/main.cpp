#include <iostream>
#include "Vector.h"
using namespace std;

int main() {
    // a test program
    std::cout << "Test Program:" << std::endl;
    cout<<"Test default ctor"<<endl;
    Vector<int> s;
    s.show();
    cout<<"Test ctor with size"<<endl;
    Vector<int> t(10);
    //member function show will told you the condition of the vector
    t.show();
    cout<<"test the push back"<<endl;
    for(int i=0;i<10;i++){
        t.push_back(i);
    }
    t.show();
    cout<<"test the copy ctor"<<endl;
    Vector<int> r(t);
    r.show();
    for(int i=0;i<r.size(); i++){
        cout<<r[i]<<endl;
    }
    cout<<"test the size method"<<endl;
    cout<<r.size()<<endl;
    cout<<"test the [] operation"<<endl;
    cout<<"The 4th element in the vector t is:"<<t[4]<<endl;
    t.show();
    cout<<"test the clear method"<<endl;
    t.clear();
    cout<<"test the empty method"<<endl;
    cout<<t.empty()<<endl;
    cout<<"test the inflate method"<<endl;
    Vector<int> p(1);
    p.show();
    p.push_back(1);
    p.push_back(2);
    p.show();
    //p[1] = 100;
    //cout<<p[0]<<endl;
    //cout<<t[0]<<endl;
    //cout<<t[1]<<endl;
    //这里会抛出异常使得程序终止
    //test the error process of []

    int a=t.at(200);
    cout<<a<<endl;
    // system("pause");
    return 0;
}
