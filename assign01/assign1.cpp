/*
OOP Assignment 01 Where's Waldorf? - 20151676 «—ºÆ¡÷

# EXCEPTION CASE #
1. Non-integer input or nonpositive input for number of sets to search for and number of words to find.
2. Non-alphabetic input (including space, hypen, and so on) is entered to grid or words.
3. Out of range
	- row and column (m and n) of grid : 1 <= m, n <= 100
	- number of words k : 1 <= k <= 100
4. Length of words in each row of grid shorter than column number.
*/

#include <iostream>
#include <cstring>

using namespace std;

typedef struct { int x, y; } POSITION;
POSITION position[8] = { { 0, -1 },{ 1, -1 },{ 1, 0 },{ 1, 1 },{ 0, 1 },{ -1, 1 },{ -1, 0 },{ -1, -1 } };
/*
For searching grid, a recursive backtracking algortihm will be used.
A struct POSITION is a set of coordinates (x, y) which indicate 8 directions to search from current position.
By searching all possible positions in the grid from current location, these coordinates will be used.

(0, -1) : down ; (1, -1) : right down ; (1, 0) : right  ; (1, 1) : right up ;
(0, 1) : up ; (-1, 1) : left up ; (-1, 0) : left ; (-1, -1) : left down;

*/
int row, col;

bool search(char** grid, int r, int c, char* words) // Function for searching given words. TRUE if searching is sucessful, FALSE if not.
{
	int curr, r_0, c_0, index;
	for (curr = 0; curr < 8; curr++)
	{
		for (r_0 = r, c_0 = c, index = 0; words[index] != '\0'; index++)
		{
			if ((r_0 < 0) || (r_0 > row) || (c_0 < 0) || (c_0 > col)) break; // EXCEPTION : Searching should be within grid.
			if (grid[r_0][c_0] == words[index])
			{
				r_0 += position[curr].x, c_0 += position[curr].y; // recursive backtracking search on all 8 possible directions
			}
			else break;
		}
		if (words[index] == '\0') return true;
	}
	return false;
}

int main()
{
	int i, j, r, c, numOfSearch, numOfWords;
	bool found = false; // Checking if searching is completed or not.
	char words[100]; // Storing words to search in the grid

	cin >> numOfSearch;
	if ((numOfSearch <= 0) || cin.fail()) return EXIT_FAILURE; // EXCEPTION 1
	for (int x = 1 ; x <= numOfSearch ; x++)
	{
		cin >> row >> col;
		if (row < 1 || col < 1 || row > 100 || col > 100) return EXIT_FAILURE; // EXCEPTION 3

		char** grid = new char*[row + 1];
		for (i = 0; i <= row; ++i) grid[i] = new char[col + 1]; // Dynamically allocate 2D grid for storing a list of words

		for (i = 0; i < row; i++)
		{
			for (j = 0; j < col; j++)
			{
				cin >> grid[i][j];
				grid[i][col] = '\0'; // For avoiding heap corruption.
				if ((strlen(grid[i]) > col) || !((grid[i][j] >= 'a' && grid[i][j] <= 'z') || (grid[i][j] >= 'A' && grid[i][j] <= 'Z'))) return EXIT_FAILURE; // EXCEPTION 2, 4
			}
			for (j = 0; j < col; j++) grid[i][j] = tolower(grid[i][j]); // For making all inputs to lowercase.
		}

		cin >> numOfWords;
		if (numOfWords < 1 || numOfWords > 100 || cin.fail()) return EXIT_FAILURE; // EXCEPTION 2, 3

		for (int y = 0 ; y < numOfWords ; y ++)
		{
			cin >> words;	
			for (i = 0; i < strlen(words); i++)
			{
				words[i] = tolower(words[i]); // For making all inputs to lowercase.
				if (!((words[i] >= 'a' && words[i] <= 'z') || (words[i] >= 'A' && words[i] <= 'Z'))) return EXIT_FAILURE; // EXCEPTION 2
			}
			found = false; // Initializing check.
			 
			for (r = 0; r < row; r++) // Searching words from uppermost and leftmost position.
			{
				for (c = 0; c < col; c++)
				{
					if (grid[r][c] == words[0])
					{
						if (search(grid, r, c, words))
						{
							cout << r + 1 << ' ' << c + 1 << endl; // Printing starting location of the words found
							found = true;
						}
					}
					if (found) break;
				}
				if (found) break;
			}
		}
		for (i = 0; i < (row + 1); i++) delete[] grid[i];
		delete[] grid;
		if(x != numOfSearch) cout << endl; // If searching is done yet the cases to find are remained, they should be seperated by a blank line.
	}
	return 0;
}

/**
Sample Input1 
1 

8 11 
abcDEFGhigg 
hEbkWalDork 
FtyAwaldORm 
FtsimrLqsrc 
byoArBeDeyv 
Klcbqwikomk 
strEBGadhrb 
yUiqlxcnBjf 

4 
Waldorf 
Bambi 
Betty 
Dagbert

Sample Output1
2 5 
2 3 
1 2 
7 8 

============================
Sample Input2
10

3 3
Hpv
eHC
uoN

6
e
oC
N
e
eH
o

9 8
jajPjpVd
WJVhyowL
YZMZrqDG
rxpMiqCo
RKGCzlmG
KRjRKZKR
DIMJfQmy
dcAhazYQ
uOLWukMH

4
Q
QaW
m
au

7 10
wIkaNboMsi
BrFaMVJYgN
LZFuOWEqrW
LqZPPAYELF
guryfqoNxW
lSvrzLausE
nOFqhTIEKO

7
Yq
rEo
Ns
AqL
EN
u
ig

8 8
rAQcTNSH
tWwOiyNo
otEWWKMi
obcVgVDB
cxUdFFJZ
VlvPeyWb
XESIYRhg
VeCvGqwa

8
FVKy
Bi
Zbg
DFeIC
gVc
i
TiWgF
FdUxc

10 1
H
T
Y
a
A
u
K
O
c
f

7
u
TY
T
KOcf
A
O
c

8 10
gcTEbJMLbx
gwvWUEbvoT
EywPEmlsGc
ibRGzYHZLF
EBDWkJIHMI
PsICIkAEgO
CmOoipJWdM
hAjoghGuqz

10
IY
goj
IE
MEJ
i
L
zP
T
ZHY
IkAE

4 4
CLcj
GHtt
xhoP
rABa

3
t
LH
jcL

8 8
ZKlMdfkk
eJIsjriD
CFZWCndg
AvEIVNio
HDnODFDR
cpDwBFEZ
pwevqRnZ
aXQDjGDc

10
inVO
EZIl
vEIVNi
Z
j
c
D
D
Il
Ri

1 2
uI

1
I

1 1
B
	
7
B
B
B
B
B
B
B

Sample Output2
2 1
3 2
3 3
2 1
2 1
3 2

3 6
7 6
3 3
8 5

2 8
3 9
2 10
4 6
4 8
3 4
1 10

5 6
4 8
5 8
4 7
4 5
2 5
1 5
5 5

6 1
2 1
2 1
7 1
4 1
8 1
9 1

4 1
8 5
4 1
3 6
4 1
1 8
4 5
1 3
4 8
6 5

2 3
1 2
1 4

2 7
4 3
4 2
1 1
2 2
3 1
1 5
1 5
2 3
2 6

1 2

1 1
1 1
1 1
1 1
1 1
1 1
1 1

*/