#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

string Calculator(string str) { 

  stringstream p0;
  
  int k = 0;
  
  int i0 = 0;
  int i1 = 0;
  
  int o;

  p0.str("");
  while (str[k] != '\0') {
    if (str[k] == '(') {
      	if (k > 0) {
      		if ((str[k - 1] != '*') && 
                (str[k - 1] != '/') &&
                (str[k - 1] != '+') &&
                (str[k - 1] != '-')) {
              	str.insert(k, "*");
              	k++;
            }
        }
        i0 = k;
        k++;
        while (str[k] != ')') {
          if (str[k] == '(') {
            i0 = k;
            p0.str("");
            k++;
          } else {
            p0 << str[k];
            k++;
          }
        }
        i1 = str.find(')');
        str.replace(i0, (i1 - i0) + 1, Calculator(p0.str()));
        p0.str("");
        k = 0;
    } else {
    	k++;
    }
  }

  string s0 = "";
  string s1 = "";
  double d0 = 0.0;
  double d1 = 0.0;
  p0.str("");
  
  i0 = str.rfind('+');
  if (i0 != -1) {
  	s0 = Calculator(str.substr(0, i0));
    s1 = Calculator(str.substr(i0 + 1));
    d0 = atof(s0.c_str());
    d1 = atof(s1.c_str());
    d0 += d1;
    p0 << d0;
    return p0.str();
  }
  
  i0 = str.rfind('-');
  if (i0 != -1) {
  	s0 = Calculator(str.substr(0, i0));
    s1 = Calculator(str.substr(i0 + 1));
    d0 = atof(s0.c_str());
    d1 = atof(s1.c_str());
    d0 -= d1;
    p0 << d0;
    return p0.str();
  }
  
  i0 = str.rfind('*');
  if (i0 != -1) {
  	s0 = Calculator(str.substr(0, i0));
    s1 = Calculator(str.substr(i0 + 1));
    d0 = atof(s0.c_str());
    d1 = atof(s1.c_str());
    d0 *= d1;
    p0 << d0;
    return p0.str();
  }
  
  i0 = str.rfind('/');
  if (i0 != -1) {
  	s0 = Calculator(str.substr(0, i0));
    s1 = Calculator(str.substr(i0 + 1));
    d0 = atof(s0.c_str());
    d1 = atof(s1.c_str());
    d0 /= d1;
    p0 << d0;
    return p0.str();
  }

  return str;        
}

int main() { 
  string A = "2(4) + 15/(3 + 2) - 1";
  cout << Calculator(A);
  return 0;
}           
