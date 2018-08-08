/* 
2015167 Hahn Seok Ju
CSE241 OOP ? Assignment04 ? Reverse and Add
*/
#include <iostream>
#include <fstream>
 
using namespace std;
 
// Since all integers in this assignment are ranged between 0 to 4,294,967,295, which is exactly corresponded to the range of variable type ¡®unsigned long¡¯, I made all the variables have a type ¡®unsigned long¡¯.
unsigned long reverse(unsigned long num)
{
	unsigned long reversed = 0;
	while(num != 0)
	{
		// can extract the rightmost digit as a remainder by dividing original number into   (num % 10)
		// move the digit to the left by one in each iteration (it can be done through multiplying temporary reversed integer by 10 : reversed * 10) 
		// and then continually get the modified number (num /= 10) 
		reversed = reversed * 10 + num % 10;
		num /= 10;
	}
	return reversed; 
}
 
int main()
{
	// for cin from external file, 'input.txt'
	ifstream inputFile;
	inputFile.open("input.txt");
	streambuf *buf = cin.rdbuf(inputFile.rdbuf());
	
	int cases, index = 0;
	unsigned long* input;
 
	cin >> cases;
	// EXCEPTION : if cases to find are over 100 or under 0, terminate program
	if (!(cases > 0 & cases <= 100)) return 1;
 
	// get numbers to be tested in a unsinged long dynamic array
	input = new unsigned long[cases];
	for (int i = 0 ; i < cases ; i++) cin >> input[i];
 
	while(cases--)
	{	
		int count = 0;
		// looping until find palindrome
		// how to judge if the number is palindrome or not?
		// SIMPLE : if the number is equivalent to the result processed by reverse function, it is a palindrome
		while (input[index] != reverse(input[index]))
		{
				// summing up the reversed result to the number
				input[index] += reverse(input[index]);
				count++;
		}
		// print out results
		cout << count << ' ' << input[index] << endl;
		// move index to process the next case
		index++;
	}
	delete [] input;
 
	return 0;
}