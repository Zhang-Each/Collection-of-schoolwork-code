
#include "fraction.h"
//default ctor
fraction::fraction() {
    numerator=0;
    denominator=1;
}

//the ctor using 2 integers as parameters
fraction::fraction(int a, int b) {
    if(a*b<0){
        a=-abs(a);
        b=abs(b);
    }
    else if(b==0){
        a=0;
        b=1;
    }
    else{
        a=abs(a);
        b=abs(b);
    }
    numerator=a;
    denominator=b;
    fraction::reduction();
}

//copy ctor
fraction::fraction(const fraction &s) {
    numerator=s.numerator;
    denominator=s.denominator;
}

//member function to show a fraction
void fraction::show_fraction() {
    cout<<"----------------------------"<<endl;
    cout<<"The numerator is "<<numerator<<endl;
    cout<<"The denominator is "<<denominator<<endl;
}

//function to make reduction to the fraction
void fraction::reduction() {
    if(numerator==0){
        denominator=1;
        return ;
    }
    int i,m=min(abs(numerator), abs(denominator));
    for(i=m;i>=2;i--){
        if(numerator%i==0&&denominator%i==0){
            numerator/=i;
            denominator/=i;
            break;
        }
    }
}

//overload the + operation
const fraction fraction::operator+(const fraction &s) {
    if(denominator==s.denominator){
        return fraction(numerator+s.numerator, denominator);
    }
    else{
        // cout<<numerator*s.denominator+denominator*s.numerator<<endl;
        // cout<<denominator*s.denominator<<endl;
        return fraction(numerator*s.denominator+denominator*s.numerator, denominator*s.denominator);
    }
}


// overload the - operation
const fraction fraction::operator-(const fraction &s) {
    if(denominator==s.denominator){
        return fraction(numerator-s.numerator, denominator);
    }
    else{
        return fraction(numerator*s.denominator-denominator*s.numerator, denominator*s.denominator);
    }
}

// overload the * operation
const fraction fraction::operator*(const fraction &s) {
    return fraction(numerator*s.numerator, denominator*s.denominator);
}

//overload the / operation
const fraction fraction::operator/(const fraction &s) {
    return fraction(numerator*s.denominator, denominator*s.numerator);
}

// overload the == operation
bool fraction::operator==(const fraction &s) {
    double a=(numerator*1.0)/(denominator*1.0);
    double b=(s.numerator*1.0)/(s.denominator*1.0);
    return (a==b);
}

// overload the != operation
bool fraction::operator!=(const fraction &s) {
    return !(*this==s);
}

// overload the > operation
bool fraction::operator>(const fraction &s) {
    double a=(numerator*1.0)/(denominator*1.0);
    double b=(s.numerator*1.0)/(s.denominator*1.0);
    return (a>b);
}

// overload the <= operation
bool fraction::operator<=(const fraction &s) {
    return !(*this>s);
}

// overload the >= operation
bool fraction::operator>=(const fraction &s) {
    return (*this==s)||(*this>s);
}

// overload the < operation
bool fraction::operator<(const fraction &s) {
    return (*this<=s)&&(*this!=s);
}

// overload the cast change of double
fraction::operator double() const {
    return (double)numerator/(double)denominator;
}

// overload the cast change of string
fraction::operator string() const {
    return to_string(numerator)+"/"+to_string(denominator);
}

// overload the cast change of float with n floats
double fraction::chang_to_float(int n) const {
    return (int)((double)(*this)*pow(10,n))*1.0/pow(10,n);
}

// overload the cin and cout
istream& operator>>(istream &is, fraction& obj){
    cout<<"Please input the numerator and denominator:"<<endl;
    is>>obj.numerator>>obj.denominator;
    obj.reduction();
    return is;
}

ostream& operator<<(ostream &os, fraction& obj){
    cout<<"The fraction is : ";
    os<<string(obj)<<endl;
    return os;
}