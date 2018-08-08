/*
20151676 Hahn Seokju
CSE241 OOP assignment5 - Knapsack Problem
*/
#include <iostream>
#include <cstdlib>

#define LL long long
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

using namespace std;

LL** solve(LL** WC, int capacities, int numOfItems)
{
	// prepare Dynamic Programming Table using dynamic 2d array
	// table size : (number of items + 1) * (weight of knapsack + 1)
	// initialize all cells in the table to 0
	LL** DPtable;
	DPtable = new LL*[numOfItems + 1]; for (int i = 0 ; i <= numOfItems ; i++) DPtable[i] = new LL[capacities + 1];
	for (int i = 0 ; i <= numOfItems ; i++) for (int j = 0 ; j <= capacities ; j++) DPtable[i][j] = 0;
	// fill in each cell of the Dynamic Programming Table
	for (int i = 1 ; i <= numOfItems ; i++) for (int j = 0 ; j <= capacities ; j++) DPtable[i][j] = (j < WC[i - 1][0]) ? DPtable[i - 1][j] : DPtable[i][j] = MAX(DPtable[i - 1][j], DPtable[i - 1][j - WC[i - 1][0]] + WC[i - 1][1]);
	// return a pointer of the Dynamic Programming Table 
	return DPtable;
}

int main()
{
	int cases, items, capacity, tableSize; 
	LL **WC, **answer;
	// get number of test cases
	// EXCEPTION : less than 100 test cases should be considered
	cin >> cases; if ((cases < 1) | (cases > 100)) return EXIT_FAILURE;
	while (cases--)
	{
		// candidates input using dynamic 2d array
		// EXCEPTION : items should be in a range between 3 to 100000
		cin >> items; if ((items < 3) | (items > 100000)) return EXIT_FAILURE;
		WC = new LL*[items]; for (int i = 0 ; i < items ; i++) WC[i] = new LL[2];
		capacity = 0;

		// save pairs of inputs in each row of the 2d array which indicates (weight, cost) of each item
		for (int i = 0 ; i < items ; i++)
		{
			for (int j = 0 ; j < 2 ; j++) cin >> WC[i][j];
			// EXCEPTION : weight of each item should be either 1 or 2
			// EXCEPTION : cost of each item should be in a range between 1 to 10^9
			if ((WC[i][0] < 1) | (WC[i][0] > 2)) return EXIT_FAILURE;
			if ((WC[i][1] < 1) | (WC[i][1] > 1000000000)) return EXIT_FAILURE;
			// capacity is equal to 1 to the sum of weights of all items
			capacity += WC[i][0];
		}
		// solve the problem and print the answer
		answer = solve(WC, capacity, items);
		for (int i = 1 ; i <= capacity ; i++) cout << answer[items][i] << ' ';
		
		// free dynamic 2d array for the next input
		for (int i = 0 ; i < items ; i++) delete WC[i]; delete WC;
		for (int i = 0 ; i <= items ; i++) delete answer[i]; delete answer;
		cout << endl;
	}
	return 0;
}
