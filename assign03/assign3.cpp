/*
20151676 Seokju Hahn
CSE241 - Assignment03 - Counting Words 
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

// function to count all mathces of pattern string in the text string (text string is parsed by words)
int countWords(string pattern, string text)
{
	// pattern occurrences in the text will be assigned to parameter 'count'
	int count = 0;
	// pattern with no wildcard case - just match if the pattern is a substring or not.
	if (pattern.find('*') == string::npos && pattern.find('?') == string::npos)
	{
		size_t startPos = text.find(pattern[0]);
		while (startPos != string::npos)
		{
			for (int i = startPos, j = 0 ; j < pattern.length() ; i++, j++)
				if (pattern[j] != text[i]) return 0;
				else if (i == text.length()) break;
			count++;
			startPos = text.find(pattern[0], startPos + 1);
		}
		return count;
	}
	// pattern with wildcard '?' case
	else if (pattern.find('*') == string::npos && pattern.find('?') != string::npos)
	{
		int patind = 0;
		// find the first position of no '?'
		while (pattern[patind] == '?') patind++;
		// special case - pattern composed of only '?'(s) - compare whether having the same length or not
		if (patind == pattern.length())
		{
			if (text.length() == patind)
			{
				count++;
				return count;
			}
			else return 0;
		}
		if (text.find(pattern[patind]) == string::npos) return 0;
		// compare pattern and text by character one by one
		// if '?' occurrs, skip it, and move to the next index, continue matching
		size_t j = text.find(pattern[patind]);
		for (int i = patind ; i < pattern.length() ; i++, j++)
		{
			if (pattern[i] == '?') continue;
			if (pattern[i] != text[j]) return 0;
		}
		count++;
		return count;
	}
	// pattern with wildcard '*' or '?' case
	else if (pattern.find('*') != string::npos)
	{
		// split the pattern on the basis of '*' wildcard(s) position(s)
		string fore, rear;
		vector<size_t> asters;
		// position(s) of '*' wildcard(s) will be saved in the vector container 'asters'
		size_t asterPos = pattern.find('*', 0);
		while (asterPos != string::npos)
		{
			asters.push_back(asterPos);
			asterPos = pattern.find('*', asterPos + 1);
		}
		// fore part is a substring before the very first '*'
		fore = pattern.substr(0, asters[0]);
		size_t forePos = text.find(fore);
		// at first, find whether the substring fore is occurred
		while (forePos != string::npos)
		{
			bool done = false;
			// and then, match all the possible rear substring(s) after the fore position 
			// rear will be composed of the characters between n-th and (n + 1)-th '*' (n = 1, 2, ...)
			for (int j = 0 ; j < asters.size(); j++)
			{
				rear = (j + 1 > asters.size()) ? pattern.substr(asters[j] + 1, pattern.length() - asters[j] - 1) : pattern.substr(asters[j] + 1, asters[j + 1] - asters[j] - 1);
				size_t rearPos = text.find(rear, forePos + fore.length());
				if (j > 0) rearPos = text.find(rear, rearPos + rear.length());
				if (rearPos == string::npos) return 0;
				done = true;
			}
			if (done)
			{
				count++;
				// if the first match is successful, also check when the starting point (fore position) is changed
				forePos = text.find(fore, forePos + 1);
			}
		}
		return count;
	}
}

int main()
{
	int cases, numOfWords = 0;
	string input[1000], text, tempBuffer, tempWord;
	vector<string> words;
	
	ifstream inputFile;
	inputFile.open("input.txt");
	streambuf *buf = cin.rdbuf(inputFile.rdbuf());
	
	cin >> cases;
	cin.get(); cin.get();
	
	for (int i = 0 ; i < cases ; i++)
	{	
		getline(cin, input[i]);
		// change all the characters in input word to the lowercase
		transform(input[i].begin(), input[i].end(), input[i].begin(), ::tolower);
		// if input word has an '*' at the first or the last position, it is meaningless
		// thus, remove it from the input string...
		int len = input[i].length();
		while (input[i][0] == '*' || input[i][len - 1] == '*')
		{
			if (input[i][0] == '*') 
			{
				input[i] = input[i].substr(1, len - 1);
				len -= 1;
			}
			if (input[i][len - 1] == '*') input[i] = input[i].substr(0, len - 1);
			{
				input[i] = input[i].substr(0, len - 1);
				len -= 1;
			}
		}
		cin.get();
	}
	
	while(!cin.fail())
	{
		getline(cin, tempBuffer, '\n');
		tempBuffer = ' ' + tempBuffer;
		text += tempBuffer;
	}
	// change whole given text to the lowercase letters
	transform(text.begin(), text.end(), text.begin(), ::tolower);
	// parse the text by a space
	stringstream stringInput (text);
	// and save each splitted word in the vector container 'words'
	while (stringInput >> tempWord) words.push_back(tempWord);

	for (int i = 0 ; i < cases ; i++)
	{	
		int cnt = 0;
		// start matching all the words in the text and pattern string inputs. 
		for (vector<string>::size_type j = 0; j < words.size(); j++)
		{
			cnt += countWords(input[i], words[j]);
		}
		cout << cnt << endl;
		cout << endl;
	}
	return 0;
}

