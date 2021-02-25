#include <iostream>
#include "fraction.h"

int main() {
    //some test cases
    //test the input and output of the fraction
    fraction x;
    cin>>x;
    cout<<x;
    x.show_fraction();
    //test the calculation of 2 fractions, you can change the value of a,b to make a new test
    fraction a(100,-300);
    a.show_fraction();
    fraction b(3,5);
    b.show_fraction();
    fraction c=a+b;
    c.show_fraction();
    fraction d=a-b;
    d.show_fraction();
    fraction e=a*b;
    e.show_fraction();
    fraction f=a/b;
    f.show_fraction();
    //test for comparision of 2 fractions
    cout<<(a>=b)<<endl;
    cout<<(a==a)<<endl;
    cout<<(a<b)<<endl;
    //test cast change of fraction
    cout<<double(a)<<endl;

    cout<<string(a)<<endl;
    //conversion from a finite decimal string
    cout<<a.chang_to_float(5)<<endl;
    system("pause");
    return 0;
}
