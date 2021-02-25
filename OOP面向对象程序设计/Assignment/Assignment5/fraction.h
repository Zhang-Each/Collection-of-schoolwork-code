//
// Created by 74096 on 2020/4/29.
//

#ifndef ASSIGNMENT5_FRACTION_H
#define ASSIGNMENT5_FRACTION_H
#include<iostream>
#include<string>
#include<cmath>
using namespace std;

class fraction {
private:
    int denominator, numerator, is_positive;
    // denominator is 分母 numerator is 分子
public:
    //definition of the operations
    //default ctor
    fraction();
    //ctor using 2 integer as parameters
    fraction(int a, int b);
    //copy ctor
    fraction(const fraction & s);
    //overloading functions
    const fraction operator +(const fraction & s);
    const fraction operator -(const fraction & s);
    const fraction operator *(const fraction & s);
    const fraction operator /(const fraction & s);
    bool operator ==(const fraction &s);
    bool operator !=(const fraction &s);
    bool operator >(const fraction &s);
    bool operator <(const fraction &s);
    bool operator >=(const fraction &s);
    bool operator <=(const fraction &s);
    //change to double
    operator double() const;
    //change to string
    operator string() const;
    //string change_to_string() const;
    double chang_to_float(int n) const;
    //inserter and extractor
    friend istream& operator>>(istream &, fraction& obj);
    friend ostream& operator<<(ostream &, fraction& obj);
    // some useful member function
    void show_fraction();
    void reduction();

};


#endif //ASSIGNMENT5_FRACTION_H
