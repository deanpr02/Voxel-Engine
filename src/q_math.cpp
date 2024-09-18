#include <iostream>
#include <cmath>

//Quaternion which is 4-dimensional with 1 real part and 3 complex parts
namespace qtn{
struct Quaternion
{
float real;
float i;
float j;
float k;

    Quaternion()
    {
        this->real = 0;
        this->i = 0;
        this->j = 0;
        this->k = 0;
    }

    Quaternion(float real, float i, float j, float k)
    {
        this->real = real;
        this->i = i;
        this->j = j;
        this->k = k;
    }
    
    //add two Quaternion objects together
    Quaternion operator+(const Quaternion& other) const 
    {
        return Quaternion(real+other.real,i+other.i,j+other.j,k+other.k);
    }

    //return the conjugate of a Quaternion
    Quaternion conjugate()
    {
        return Quaternion(real,-i,-j,-k);
    }

    float norm(){
        return sqrt((pow(real,2))+(pow(i,2))+(pow(j,2))+(pow(k,2)));
    }

    Quaternion normalize()
    {
        float norm = this->norm();
        return Quaternion(real/norm,i/norm,j/norm,k/norm);
    }

    float dot(Quaternion q)
    {
        return real*q.real + i*q.i + j*q.j + k*q.k;
    }


    Quaternion cross(Quaternion q)
    {
        return Quaternion(0,j*q.k-q.j*k,i*q.k-q.i*k,i*q.j-q.i*j);
    }

    Quaternion operator*(const float other) const
    {
        return Quaternion(other*real,other*i,other*j,other*k);
    }

    
    Quaternion operator*(const Quaternion& other) const 
{
    float new_real = real*other.real - i*other.i - j*other.j - k*other.k;
    float new_i = real*other.i + i*other.real + j*other.k - k*other.j;
    float new_j = real*other.j - i*other.k + j*other.real + k*other.i;
    float new_k = real*other.k + i*other.j - j*other.i + k*other.real;

    return Quaternion(new_real, new_i, new_j, new_k);
}


};


}