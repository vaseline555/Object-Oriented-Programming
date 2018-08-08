#include "IntArray.h" 
#include <iostream> 

using namespace std;

void empty(IntArray& il) { while (!il.empty()) il.pop(); }

int main()
{
	cout << "------------- test 1--------------" << endl;
	IntArray s1;
	for (int i = 0; i < 10; i++) s1.push(i);
	cout << s1 << endl; // 9 8 7 6 5 4 3 2 1 0
	cout << s1.pop() << endl; // 9
	for (int i = 0; i < 10; i++) s1[i] = i; // this should not reallocate memory space
	cout << s1 << endl; // 0 1 2 3 4 5 6 7 8

	IntArray s2(s1);
	cout << s2 << endl; // 0 1 2 3 4 5 6 7 8
	cout << s2.size() << endl;
	cout << s2.pop() << endl; // 0
	cout << s2.pop() << endl; // 1
	cout << s2.pop() << endl; // 2
	cout << s2.top() << endl; // 3
	cout << s2 << endl; // 3 4 5 6 7 8
	empty(s1);
	if (s1.empty()) cout << "s1 is empty!" << endl;
	cout << s1 << endl;
	s1.appendCopyAtEnd(s2); // concatenate two arrays
	cout << s1 << endl; // 3 4 5 6 7 8

	IntArray s3;
	if (s3.empty()) cout << "s3 is empty!" << endl;
	s2.appendCopyAtEnd(s3); // concatenate two arrays
	cout << s2 << endl; // 3 4 5 6 7 8
	for (int i = 0; i < 10; i++) s3.push(i);
	cout << s3 << endl; // 9 8 7 6 5 4 3 2 1 0
	s3.appendCopyAtEnd(s2); // concatenate two arrays
	cout << s3 << endl; // 9 8 7 6 5 4 3 2 1 0 3 4 5 6 7 8


	IntArray a1;
	for (int i = 0; i < 10; i++) a1.push(i);
	for (int i = 0; i < 10; i++) a1[i] = i;

	IntArray a2;
	a2.push(111); a2.push(2);
	cout << a2 << endl; // 2 111
	a2 = a1;
	cout << a2 << endl; // 0 1 2 3 4 5 6 7 8 9
	a1.appendCopyAtEnd(a2);
	cout << a1 << endl; // 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9
	cout << a2 << endl; // 0 1 2 3 4 5 6 7 8 9
	a2.appendCopyAtEnd(a2);
	cout << a2 << endl; // 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9
	empty(a2);
	if (a2.empty()) cout << "a2 is empty!" << endl;
	a1.appendCopyAtEnd(a2);
	cout << a1 << endl; // 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9
	a2.appendCopyAtEnd(a2);
	cout << a2 << endl; //

	IntArray a3;
	a3.push(2015); a3.push(1676);
	cout << a3 << endl; // 1676 2015
	IntArray a4 = a3;
	cout << a4 << endl; // 1676 2015 
	empty(a2);
	//a2.top(); // print out "Error: invalid memory access" and terminate.
	//a2.pop(); // print out "Error: invalid memory access" and terminate.
	//s1[100] = 100; // print out "Error: invalid memory access" and terminate.
	
	return 0;
}
