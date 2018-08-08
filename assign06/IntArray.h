#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class IntArray
{
private:
	int nelements;
	int *elements;
	int capacity;

public:
	IntArray(int); // constructor
	IntArray(const IntArray &); // copy constructor
	~IntArray(); // destructor
	IntArray& operator= (const IntArray &); // overloading operator=

	int size() const { return capacity; } // return size of the array
	int pop(); // remove the first elements in the array
	bool empty() const { return nelements == 0; } // return true if IntArrray is empty
	int top() const; // return the top of the element in the array
	void push(int);  // push element on top of the array
	int& operator[](int); // overloading operator[]
	void appendCopyAtEnd(const IntArray&); // concatenate two arrays
	friend ostream& operator<<(ostream& os, const IntArray& arg) // print elements of an array
	{
		for (int i = 0; i < arg.nelements; i++) { os << arg.elements[i] << ' '; }
		return os;
	}
};

IntArray::IntArray(int size = 0)
{
		nelements = 0;
		elements = new int[size];
		capacity = size;
}

IntArray::IntArray(const IntArray &IntArrayObj)
{
	capacity = IntArrayObj.capacity;
	elements = new int [IntArrayObj.nelements];
	memcpy(elements, IntArrayObj.elements, IntArrayObj.nelements * sizeof(int));
	nelements = IntArrayObj.nelements;
}

IntArray::~IntArray() { delete[] elements; }

IntArray& IntArray::operator= (const IntArray& IntArrayObj)
{
	if (this != &IntArrayObj)
	{
		IntArray newIntArray(IntArrayObj);
		int *temp = newIntArray.elements;
		newIntArray.elements = elements;
		elements = temp;

		nelements = newIntArray.nelements;
		capacity = newIntArray.capacity;
	}
	return *this;
}

int &IntArray::operator[](int index)
{
	try
	{
		if (index < 0 || index > nelements) throw "Error : invalid memory access";
		if (nelements == 0) throw "Error : invalid memory access";
		return elements[index];
	}
	catch (const char* errorMessage) { cout << errorMessage << endl; exit(-1); }
}

void IntArray::push(int data)
{
	if (nelements == capacity)
	{
		IntArray newIntArray(capacity + 1);
		memcpy(newIntArray.elements, elements, nelements * sizeof(int));

		int *temp = newIntArray.elements;
		newIntArray.elements = elements;
		elements = temp;
	}
	memmove(elements + 1, elements, nelements * sizeof(int));
	elements[0] = data;
	++nelements;
	++capacity;
}

int IntArray::pop()
{
	try { if (nelements == 0) throw "Error : invalid memory access"; }
	catch (const char* errorMessage) { cout << errorMessage << endl; exit(-1); }
	int popped = elements[0];
	memmove(elements, elements + 1, nelements * sizeof(int));
	--nelements;
	--capacity;

	return popped;
}

int IntArray::top() const
{
	try { if (nelements == 0) throw "Error : invalid memory access"; }
	catch (const char* errorMessage) { cout << errorMessage << endl; exit(-1); }
	return elements[0];
}

void IntArray::appendCopyAtEnd(const IntArray& IntArrayObj)
{
	if (!IntArrayObj.empty())
	{
		if (this->empty())
		{
			delete[] elements;
			capacity = IntArrayObj.capacity;
			elements = new int[IntArrayObj.nelements];
			memcpy(elements, IntArrayObj.elements, IntArrayObj.nelements * sizeof(int));
			nelements = IntArrayObj.nelements;
		}
		else
		{
			IntArray newIntArray(capacity + IntArrayObj.capacity);
			memcpy(newIntArray.elements, elements, nelements * sizeof(int));

			int *temp = newIntArray.elements;
			newIntArray.elements = elements;
			elements = temp;

			memcpy(elements + capacity, IntArrayObj.elements, IntArrayObj.nelements * sizeof(int));
			nelements += IntArrayObj.nelements;
			capacity += IntArrayObj.capacity;
		}
		
	}
}
