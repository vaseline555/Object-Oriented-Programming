/*
20151676 Seokju Hahn
CSE241 OOP assignment7 - Linked List
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

class twoWayLinkedlist
{
public:
	class Node
	{
	public:
		int xdata, ydata; // data in node : parsed from "x-y" => (x, y)
		Node *x, *y; // pointer pointing to the next elements in horizontal direction and vertical direction
		Node(int xinput, int yinput, Node* horizontal = NULL, Node* vertical = NULL)
		{
			xdata = xinput; ydata = yinput;
			x = horizontal, y = vertical;
		}
	};

	Node* head;  // pointer pointing to the starting node (leftmost and lowermost)

	twoWayLinkedlist() { head = NULL; } // constructor
	~twoWayLinkedlist() {}; // destructor

	bool search(int x, int y, bool print); // find a node in the list
	void append(int x, int y); // add a node in the list
	void remove(int x, int y); // delete a node in the list
};

void twoWayLinkedlist::append(int x, int y)
{
	Node *curr, *next, *temp;
	// if the node to be added is smaller than any existing node, just append it to the very front!
	if (head == NULL || head->xdata > x) { head = new Node(x, y, head, NULL); }
	// if the node to be added has the same x coordinate value of that of the head node, compare y coordinate value and append
	else if (x == head->xdata)
	{
		if (y < head->ydata) { head = new Node(x, y, head->x, head); }
		else
		{
			curr = head; next = head->y;
			while (next != NULL && y > next->ydata) { curr = next; next = next->y; }
			curr->y = new Node(x, y, NULL, next);
		}
	}
	// if the node to be added has bigger x coordinate value, iterate through horizontally at first
	else if (x > head->xdata)
	{
		curr = head; next = head->x;
		while (next != NULL && x > next->xdata) { curr = next; next = next->x; }
		if (next != NULL && x == next->xdata)
		{
			// when we find the proper position of the x coordinate input value, then iterate through vertically
			// to find the proper position of the y coordinate input value

			// NO need to iterate! y coordinate input value is the smallest in this poistion!
			if (y < next->ydata) { curr->x = new Node(x, y, next->x, next); }
			// ...else case... iterate through vertical way
			else if (y > next->ydata)
			{
				temp = next;
				while (temp->y != NULL && temp->y->ydata < y) { temp = temp->y; }
				temp->y = new Node(x, y, NULL, temp->y);
			}
		}
		// if there's no matched existing node having the same value with the x coordinate input value,
		// we may definitely reached to the rightmost position of the list.
		// Thus, just make a new node to the rightmost (tail) poistion!
		else { curr->x = new Node(x, y, next, NULL); }
	}
}

void twoWayLinkedlist::remove(int x, int y)
{
	// bridge is for transfering pointer's direction (vertical <-> horizontal)
	// temp is the last house for some node to be deleted
	Node *curr, *next, *bridge, *temp;
	// if the node to be deleted has x coordinate value which is equal to that of head node,
	if (head->xdata == x)
	{
		// ...and also same y coordinate,
		if (head->ydata == y)
		{
			// (if exist) pull nodes above to downward, and delete the node
			if (head->y != NULL)
			{
				temp = head;
				head->y = temp->y; head->x = temp->x;
				delete temp;
			}
			// if it is the sole node, just remove!
			else
			{
				temp = head;
				head = head->x;
				delete temp;
			}
		}
	}
	// if the node to be deleted is not located at the head position... iterate through rightward!
	else
	{
		curr = head; next = head->x;
		while (next->xdata != x) { curr = next; next = next->x; }
		// if reached node has the same y coordinate, then start to remove this node...!
		if (next->ydata == y)
		{
			// (if exist) pull nodes above to downward, and delete the node
			if (next->y != NULL)
			{
				temp = next; curr->x = next->y; curr->x->x = next->x;
				delete temp;
			}
			// if it is the sole node, just remove!
			else
			{
				temp = next; curr->x = next->x;
				delete temp;
			}
		}
		// if reached node does not have the same y coordinate value, then iterate through upward
		else
		{
			bridge = next;
			while (bridge->y->ydata != y) { bridge = bridge->y; }
			if (bridge->y->ydata == y)
			{
				temp = bridge->y; bridge->y = bridge->y->y;
				delete temp;
			}
		}
	}
}

bool twoWayLinkedlist::search(int x, int y, bool print)
{
	// print = true if you want to see a position of the node given,
	// print = false if you just want to know whether the node exists or not.
	Node *v, *h; // v for vertical direction pointer, h for horizontal direction pointer
	int xPos = 1, yPos = 1; // indicating x and y coordinate of a certain node

	if (head == NULL) { return 0; }
	// best case! just return the position!
	else if (head->xdata == x && head->ydata == y)
	{
		if (print) { cout << '(' << xPos << ',' << yPos << ')' << endl; return 1; }
		else return 1;
	}
	// second best case! just go through horizontal axis
	else if (head->xdata == x && head->ydata != y)
	{
		// anyhow move upward, and then check if it matches
		h = head->y; yPos++; if (h != NULL && h->ydata == y) { if (print) { cout << '(' << xPos << ',' << yPos << ')' << endl; return 1; } else return 1; }
		else if (h->ydata != y)
		{
			// if not, go upward again and check...
			while (h != NULL && h->ydata != y) { h = h->y; yPos++; }
			if (h != NULL && h->ydata == y)
			{
				if (print) { cout << '(' << xPos << ',' << yPos << ')' << endl; return 1; }
				else return 1;
			}
			else { if (print) { cout << "none" << endl; return 0; } else return 0; }
		}
	}
	// worst case... go through vertical axis to find x
	else if (head->xdata != x)
	{
		// anyhow move rightward, and then check if it matches
		v = head->x; xPos++;
		// if matches, then find y coordinate value
		if (v != NULL && v->xdata == x)
		{
			// if matches and fortunately matches with y coordinate, then print the result!
			if (v->ydata == y) { if (print) { cout << '(' << xPos << ',' << yPos << ')' << endl; return 1; } else return 1; }
			// if not, go upward to find y coordinate value
			else
			{
				// anyhow move upward, and then check if it matches
				// if matches, print the result!
				h = v->y; yPos++; if (h != NULL && h->ydata == y) { if (print) { cout << '(' << xPos << ',' << yPos << ')' << endl; return 1; } else return 1; }
				// if not, go upward again
				else
				{
					while (h != NULL && h->ydata != y) { h = h->y; yPos++; }
					if (h != NULL && h->ydata == y) { if (print) { cout << '(' << xPos << ',' << yPos << ')' << endl; return 1; } else return 1; }
					else { if (print) { cout << "none" << endl; return 0; } else return 0; }
				}
			}
		}
		// if not matches, then move rightward agian to find x coordinate value
		else
		{
			while (v != NULL && v->xdata != x) { v = v->x; xPos++; }
			// if finally find x coordinate value, then start to find y coordinate value
			if (v != NULL && v->xdata == x)
			{
				// if matches, YEAH!, just print the result!
				if (v->ydata == y) { if (print) { cout << '(' << xPos << ',' << yPos << ')' << endl; return 1; } else return 1; }
				// if not... again go through upward to find y coordinate value
				else
				{
					h = v->y; yPos++;
					while (h != NULL && h->ydata != y) { h = h->y; yPos++; }
					// if finally find y coordinate value, too, end up here...! print the result!
					if (h != NULL && h->ydata == y) { if (print) { cout << '(' << xPos << ',' << yPos << ')' << endl; return 1; } else return 1; }
					// if not, definitely there's no element you want to find
					else { if (print) { cout << "none" << endl; return 0; } else return 0; }
				}
			}
			// if you cannt find x coordinate value, you don't even have to find y coordinate value! no elements in the list!
			else { if (print) { cout << "none" << endl; return 0; } else return 0; }
		}
	}
}

int main()
{
	int t, ii, ic, xinput, yinput; // t : test cases, ii : items to put in, ic : items to check
	bool check = false; // true if >> (add) operator is given, false if << (delete) operator is given.
	// get input file from "input.txt"
	ifstream inputFile;
	inputFile.open("input.txt");
	streambuf *buf = cin.rdbuf(inputFile.rdbuf());
	// number of test cases should be in range of 1 to 10
	cin >> t; if (t < 1 || t > 10) return EXIT_FAILURE;

	while (t--)
	{
		twoWayLinkedlist L; // declare Linkedlist class container
		char s; // s : start sign ('-')
		cin >> s; if (s != '-') return EXIT_FAILURE; // if proper start sign is not given, terminate the program
		// number of items to put in, having a range between 1 to 100
		cin >> ii; if (ii < 1 || ii > 100) return EXIT_FAILURE;
		// dynamically allocate 2d containers for the first inputs
		char **fi = new char*[ii]; // fi : the first inputs
		for (int i = 0; i < ii; i++) fi[i] = new char[10];
		for (int i = 0; i < ii; i++)
		{
			cin >> fi[i];
			check = (fi[i][0] == '>') ? true : false;
			int dashPos = string(fi[i]).find('-');
			// parse the input string to integer x and integer y values
			xinput = atoi(string(fi[i]).substr(2, dashPos - 1).c_str());
			yinput = atoi(string(fi[i]).substr(dashPos + 1, strlen(fi[i]) - dashPos - 1).c_str());
			// if adding a node is required, first check if the node is in the list
			// if not, then append a new node to the list
			if (check) if (!L.search(xinput, yinput, false)) L.append(xinput, yinput);
			// if deleting a node is required, likewise, check if the node is in the list
			if (!check)
			{
				// if it exists, then remove, else throw an error
				try 
				{
					if (L.search(xinput, yinput, false)) L.remove(xinput, yinput);
					else throw "Cannot delete the node (NOT EXIST in the list!)";
				}
				catch (const char* errorMessage) { cout << errorMessage << endl; return EXIT_FAILURE; }
			}
			check = false;
		}
		// number of items to check having a range between 1 to 100
		cin >> ic; if (ic < 1 || ic > 100) return EXIT_FAILURE;
		// dynamically allocate 2d containers for the first inputs
		char **si = new char*[ic]; // si : the second inputs
		for (int i = 0; i < ic; i++) si[i] = new char[10];
		// starting sign before printing an output
		cout << '-' << endl;
		for (int i = 0; i < ic; i++)
		{
			cin >> si[i];
			int dashPos = string(si[i]).find('-');
			// parse the input string to integer x and integer y values
			xinput = atoi(string(si[i]).substr(0, dashPos).c_str());
			yinput = atoi(string(si[i]).substr(dashPos + 1, strlen(fi[i]) - dashPos - 1).c_str());
			// and delivering the parsed result to the search function of the list, get an printed result
			L.search(xinput, yinput, true);
		}
		// delete dynamically allocated arrays for the first and the second inputs
		for (int i = 0; i < ii; i++) delete[] fi[i]; delete[] fi;
		for (int i = 0; i < ic; i++) delete[] si[i]; delete[] si;
	}
	// bye bye
	return 0;
}
