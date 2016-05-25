#include <iostream>
#include <sstream>
#include <stdio.h>
#include <limits.h>

using namespace std;

string configToString(int* c, int size) {
  	int* r = new int[size];
	stringstream ss;
  	for (int i = 0; i < size; i++) {
  		r[c[i]] = i;
    }
  	for (int i = 0; i < size; i++) {
  		ss << "(" << i + 1 << "-" << r[i] + 1 << ")";
    }
  	return ss.str();
}

int** subMatrix(int** m, int s, int r, int c) {
  int size = s - 1;
  int** rm = new int*[size];
  for (int n = 0; n < size; n++) {
  	rm[n] = new int[size];
  }
  for (int i = 0; i < size; i++) {
    if (i >= r) {
      for (int j = 0; j < size; j++) {
        if (j >= c) {
        	rm[i][j] = m[i+1][j+1];
        } else {
        	rm[i][j] = m[i+1][j];
        }
      }
    } else {
      for (int j = 0; j < size; j++) {
        if (j >= c) {
        	rm[i][j] = m[i][j+1];
        } else {
        	rm[i][j] = m[i][j];
        }
      }
    }
  }
  return rm;
}

int* findOptimal(int** m, int size) {
	int min = INT_MAX;
  	int* min_config = new int[size];
  	int* current_config = new int[size];
    int* sub_config;
  	int cost;

  	for (int i = 0; i < size; i++) {
      current_config[0] = i;
      sub_config = findOptimal(subMatrix(m, size, i, 0), size - 1);
      for (int j = 0; j < size - 1; j++) {
      	current_config[j + 1] = sub_config[j];
        if (current_config[j + 1] >= current_config[0]) {
          current_config[j + 1]++;
        }
      }
      cost = 0;
      for (int k = 0; k < size; k++) {
      	cost += m[current_config[k]][k];
      }
      if (cost < min) {
        min = cost;
        for (int n = 0; n < size; n++) {
        	min_config[n] = current_config[n];
        }
      }
    }
  	return min_config;
}

string OptimalAssignments(string strArr[]) { 
  int size = 0;
  for (int i = 0; i < strArr[0].length(); i++) {
    if (strArr[0][i] == ',') {
    	size++;
    }
  }
  size++;
  int** input = new int*[size];
  for (int n = 0; n < size; n++) {
  	input[n] = new int[size];
  }
  stringstream ss;
  for (int j = 0; j < size; j++) {
    int c = 0;
    for (int k = 1; k < strArr[j].length(); k++) {
      if ((strArr[j][k] != ',') && (strArr[j][k] != ')')){
      	ss << strArr[j][k];
      } else {
      	sscanf(ss.str().c_str(), "%d", &input[j][c]);
        ss.str("");
        c++;
      }
    }
  }
  return configToString(findOptimal(input, size), size);    
}

int main() { 
  string A[] = {"(5,4,2)","(12,4,3)","(3,4,13)"};
  cout << OptimalAssignments(A);
  return 0;
}           
