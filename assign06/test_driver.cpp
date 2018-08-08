#include "IntArray.h"
#include <iostream>

using namespace std;

void empty(IntArray& il) {
  while (!il.empty())
  il.pop();
}

int main() {
  cout << "------------- test 1--------------" << endl;
  IntArray s1;

  for (int i = 0; i < 10; i++) s1.push(i);
  cout << s1 << endl; // 9 8 7 6 5 4 3 2 1 0

  for (int i = 0; i < 10; i++) s1[i] = i; 
  // this should not reallocate memory space 
  cout << s1 << endl; // 0 1 2 3 4 5 6 7 8 9 
  
  IntArray s2(s1);
  empty(s1);
  s1.appendCopyAtEnd(s2); //appended by an empty list
  cout << s1 << endl; // 0 1 2 3 4 5 6 7 8 9
  s1[100] = 100; // print out "Error: invalid memory access" and terminate.
}
