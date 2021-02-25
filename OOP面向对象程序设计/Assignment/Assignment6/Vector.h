//
// Created by 74096 on 2020/5/12.
//

#ifndef ASSIGNMENT6_VECTOR_H
#define ASSIGNMENT6_VECTOR_H
#include<iostream>
#include<stdexcept>

using namespace std;


template <class T>
class Vector {
public:
    Vector();                      // creates an empty vector
    Vector(int size);              // creates a vector for holding 'size' elements
    Vector(const Vector& r);       // the copy ctor
    ~Vector();                     // destructs the vector
    T& operator[](int index);      // accesses the specified element without bounds checking
    T& at(int index);              // accesses the specified element, throws an exception of type 'std::out_of_range' when index <0 or >=m_nSize
    int size() const;		 // return the size of the container
    void push_back(const T& x);    // adds an element to the end
    void clear();                  // clears the contents
    bool empty() const;            // checks whether the container is empty
    void show();

private:
    void inflate();                // expand the storage of the container to a new capacity, e.g. 2*m_nCapacity
    T *m_pElements;                // pointer to the dynamically allocated storage
    int m_nSize;                   // the number of elements in the container 已经有的元素个数
    int m_nCapacity;               // the number of elements that can be held in currently allocated storage 最多能存放的元素个数
};

// default constructor
template <class T>
Vector<T>::Vector()
{
    m_nCapacity=3;// a default value
    m_nSize=0;
    m_pElements=NULL;
}

// a function to show the vector container
template <class T>
void Vector<T>::show()
{
    cout<<"The number in the vector is:"<<m_nSize<<endl;
    cout<<"The number of total vector is:"<<m_nCapacity<<endl;
}

// destructor function
template <class T>
Vector<T>::~Vector()
{
    cout<<"Delete a vector!"<<endl;
    delete[] m_pElements;
    m_nSize=0;
    m_nCapacity=0;
}

// constructor using a parameter as size
template <class T>
Vector<T>::Vector(int size)
{
    // a default ctor with size, the elements from 0 to size-1 will be 0
    m_nSize=size;
    m_nCapacity=size;
    m_pElements=new T[size];
    for(int i=0;i<size; i++){
        m_pElements[i] = 0;
    }
}

// the copy constructor
template <class T>
Vector<T>::Vector(const Vector& r)
{
    m_nSize=r.m_nSize;
    m_nCapacity=r.m_nCapacity;
    m_pElements=new T[m_nCapacity];
    memcpy(m_pElements, r.m_pElements, sizeof(T) * m_nSize);
}

// return the size of the vector contains now, not the max size
template <class T>
int Vector<T>::size() const
{
    return m_nSize;
}

// function to clear the vector
template <class T>
void Vector<T>::clear()
{
    m_nSize=0;
    m_nCapacity=0;
    m_pElements=NULL;
}

//function to check whether it's empty
template <class T>
bool Vector<T>::empty() const
{
    return m_nCapacity == 0 || m_nSize == 0;
}

//function to push a value on the back of vector
template <class T>
void Vector<T>::push_back(const T &x)
{
    if(m_nSize<m_nCapacity){
        m_pElements[m_nSize++]=x;
    }
    else{
        //double the space if not enough
        inflate();
        m_pElements[m_nSize++]=x;
    }
}

// function to return the value of the index
template <class T>
T& Vector<T>::operator[](int index)
{
    return m_pElements[index];
}

// function to return the value of the index with safety check
template <class T>
T& Vector<T>::at(int index)
{
    //cout<<"In the at:"<<endl;
    if(index<0||index>=m_nSize){
        throw out_of_range("Index out of range!!!!!!");
        //throw IndexError(index);
    }
    return m_pElements[index];
}

// make the vector double size
template <class T>
void Vector<T>::inflate()
{
    T* s=new T[m_nCapacity];
    for(int i=0;i<m_nSize;i++){
        s[i]=m_pElements[i];
    }
    m_nCapacity*=2;
    m_pElements=new T[m_nCapacity];
    for(int i=0;i<m_nSize;i++){
        m_pElements[i]=s[i];
    }
}


#endif //ASSIGNMENT6_VECTOR_H
