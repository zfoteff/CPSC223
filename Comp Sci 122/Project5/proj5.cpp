/*
Class: CPSC 122-01
Team Member 1: Zac Foteff
Team Member 2: None
Submitted by: Zac Foteff
GU Username: zfoteff
File Name: proj5.cpp
Program defines a Class named MyString.
Defines public functions to be used in proj5Tst.cpp
To Build: g++ proj5Tst.cpp proj5.cpp
To Execute: ./a.out
*/

#include "proj5.h"
#include <cstring>
#include <iostream>
#include <cstring>
using namespace std;

MyString::MyString(char const* strIn){
  str = new char[strlen(strIn) + 1];
  strcpy(str,strIn);
}

MyString::~MyString(){ // is called automatically at end of program
  delete [] str; // deletes MyString object from memory
}

void MyString::MyStrDisplay(){
  cout << str << endl;
}

int MyString::MyStrlen(){
  char comp;
  int i;

  for(i = 0; comp != '\0'; i++){
    comp = str[i];
  }

  return i;
}

void MyString::MyStrcpy(char const* strIn){
  int i;
  for(i = 0; i< strlen(strIn); i++){
    str[i] = strIn[i];
  }
  str[i] = '\0';
}

int MyString::MyStrcmp(char const* strIn){
  // if str comes before strIn alphabetically
  if(str[0] < strIn[0]){
    return -1;
  }

  //if both start with same character
  else if(str[0] == strIn[0]){
    return 0;
  }

  //if strIn comes before str alphabetically
  else if(str[0] > strIn[0]){
    return 1;
  }
}

int MyString::Find(char const* strIn)
{
  int index = -1;
  for(int i = 0; i< strlen(str) - strlen(strIn); i++)
  {
    if(str[i] == strIn[0])
    {
      cout<<"Here i = "<<i<<" ";
      for(int j = 0; j< strlen(strIn); j++)
      {
        if(str[i+j] == strIn[j]){
          cout<<"x";
          index = i;
        }
        else
          index = -1;
      }
    }
  }
  return index;
}
