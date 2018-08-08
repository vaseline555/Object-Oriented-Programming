/*

Core idea :
	a)	A length of original file is the sum of the length of the shortest fragment and the longest fragment.
	b)	Suppose X be the shortest one and Y be the longest one.Either ¡®X + Y¡¯ or ¡®Y + X¡¯(call it ¡®candidate¡¯) CAN be an original file.So, I at first make a possible candidate.
	c)	To make a possible candidate easily and efficiently, I sort fragments inputs in ascending order.
	d)	Then, I can get an original file¡¯s length(int filel), the shortest fragment¡¯s length(int minl), and the longest fragment¡¯s length(int maxl).After that, I combined candidate only with fragments having the same length with minl or maxl.
		Due to the fact in b), candidate that can be combined from fragments of which length is not equal to minl or maxl(i.e.fragments of which length is((minl + maxl) // 2) etc.,) don¡¯t have to be considered.
	e)	Each candidate SEEMS to be an answer.However, it should be checked whether it can also be combined with fragments that are not used to combine the candidate.
		It should be checked that exactly same combination can be made with all the fragments EXCEPT the ones used to make candidate.If it is not, the candidate is not equal to the original file.
	f)	To implement e), I make a Boolean marker ¡®bool check[MAX_NUM]¡¯, which is allocated to each fragment as a marker(indicating that the fragments is considered or not) in every case.
	g)	When the candidate is combined during implementation(as I said in b), two different candidates can be generated from a pair of fragmens), it is directly passed to get_answer function to realize e).In the get_answer function, the function checks whether fragments that were not used to make candidate(which can be known if check[i] is false) can be combined to make passed candidate.If it can be, the marker is turned to true.After all, if all markers are turned to true, i.e.original file is retrieved, the get_answer function returns true, however, if at most 1 marker have false value, the function returns false.
	h)	If the get_answer function returns true, the candidate will be printed.Each answer will be separated by a line unless test cases are done.

*/

#include <iostream>
#include <string>
#include <fstream>

#define MAX_NUM 144

using namespace std;

bool get_answer(string candidate, int size, string* input, bool* check)
{
	for (int i = 0; i < size; i++)
		for (int j = i + 1; j < size; j++)
			if (!check[i] && !check[j] && input[i] + input[j] == candidate || input[j] + input[i] == candidate)
				check[i] = check[j] = true;

	for (int k = 0; k < size; k++) if (!check[k]) return false;
	return true;
}

int main()
{
	int cases, size, filel, minl, maxl;
	bool done, check[MAX_NUM];
	string input[MAX_NUM];

	// standard input from input.txt
	ifstream inputFile;
	inputFile.open("input.txt");
	streambuf *buf = cin.rdbuf(inputFile.rdbuf());

	cin >> cases;
	// for flushing out standard input (enter or spaces will be removed)
	for (int i = 0; i < 2; i++) while (cin.get() != '\n');

	while (cases--)
	{
		// get file fragments to string ¡®input¡¯
		// At the same time, file size can be derived
		for (size = 0;; size++)
		{
			getline(cin, input[size]);
			if (input[size] == "") break;
		}
		// EXCEPTION : if odd number of file fragments are entered or the file size is over 256, program will be terminated.
		if (size % 2 != 0 || size > 256) return EXIT_FAILURE;

		// for sorting the file fragments in ascending order using string::swap
		for (int i = 0; i < size; i++)
		{
			int j = 1;
			if (input[i].length() == 0) break;
			for (j += i; j < size && input[j].length() != 0; j++)
			{
				if (input[i].length() > input[j].length()) input[i].swap(input[j]);
			}
		}
	
		// get an orginal length of the file (filel), shortest length of the file fragments (minl), longest length of the file fragment (maxl)
		filel = input[0].length() + input[size - 1].length();
		minl = input[0].length();
		maxl = input[size - 1].length();

		// flag for checking finding answer is done or not
		done = false;

		// for fragments having the same length as minl and maxl,
		for (int i = 0; input[i].length() == minl; i++)
		{
			for (int j = size - 1; input[j].length() == maxl; j--)
			{
				// initialize marker (see f) above) for each fragment
				for (int p = 0; p < size; p++) check[p] = false;
				// start checking if combination in (X + Y) way is vaild by passing it to get_answer function
				check[i] = check[j] = true;
				if (get_answer(input[i] + input[j], size, input, check) && (input[i] + input[j]).length() == filel)
				{
					// if it is valid, print answer, and escape from the loop
					cout << input[i] + input[j] << endl;
					done = true;
					break;
				}

				// initialize marker for each fragment
				for (int q = 0; q < size; q++) check[q] = false;
				// start checking if combination in (Y + X) way is vaild by passing it to get_answer function
				check[i] = check[j] = true;
				if (get_answer(input[j] + input[i], size, input, check) && (input[j] + input[i]).length() == filel)
				{
					// if it is valid, print answer, and escape from the loop
					cout << input[j] + input[i] << endl;
					done = true;
					break;
				}
			}
			if (done) break;
		}
		// if more test cases are remained, separating the result by line
		if (cases) cout << endl;
	}
	return 0;
}


/*
version 2
#include <iostream>
#include <string>
#include <fstream>

#define MAX_NUM 288

using namespace std;

bool get_answer(string candidate, int size, string* input, bool* check)
{
	for (int i = 0; i < size; i++)
		for (int j = i + 1; j < size; j++)
			if (!check[i] && !check[j] && input[i] + input[j] == candidate || input[j] + input[i] == candidate)
				check[i] = check[j] = true;

	for (int k = 0; k < size; k++) if (!check[k]) return false;
	return true;
}

int main()
{
	int cases, size, filel, minl, maxl;
	bool done, check[MAX_NUM];
	string input[MAX_NUM];

	ifstream inputFile;
	inputFile.open("input.txt");
	streambuf *buf = cin.rdbuf(inputFile.rdbuf());

	cin >> cases;
	for (int i = 0; i < 2; i++) while (cin.get() != '\n');

	while (cases--)
	{
		cin.clear();

		for (size = 0;; size++)
		{
			getline(cin, input[size]);
			if (input[size] == "") break;
		}

		if (size % 2 != 0 || size > 256) return 1;

		for (int i = 0; i < size; i++)
		{
			int j = 1;
			if (input[i].length() == 0) break;
			for (j += i; j < size && input[j].length() != 0; j++)
			{
				if (input[i].length() > input[j].length()) input[i].swap(input[j]);
			}
		}

		filel = input[0].length() + input[size - 1].length();
		minl = input[0].length();
		maxl = input[size - 1].length();

		done = false;
		for (int i = 0; input[i].length() == minl; i++)
		{
			for (int j = size - 1; input[j].length() == maxl; j--)
			{
				for (int p = 0; p < size; p++) check[p] = false; check[i] = check[j] = true;
				if (get_answer(input[i] + input[j], size, input, check) && (input[i] + input[j]).length() == filel)
				{
					cout << input[i] + input[j] << endl;
					done = true;
					break;
				}
				for (int q = 0; q < size; q++) check[q] = false; check[i] = check[j] = true;
				if (get_answer(input[j] + input[i], size, input, check) && (input[j] + input[i]).length() == filel)
				{
					cout << input[j] + input[i] << endl;
					done = true;
					break;
				}
			}
			if (done) break;
		}
		if (cases) cout << endl;
	}
	return 0;
}
*/