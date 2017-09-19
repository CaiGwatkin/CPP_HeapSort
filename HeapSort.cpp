//////////////////////////////////////////////
//	Cai Gwatkin								//
//////////////////////////////////////////////
//	This program reads in numbers from		//
//	text files, sorts adds them to a Heap,	//
//	and sorts them into ascending order		//
//////////////////////////////////////////////

#include "HeapSort.h"


int main(int argc, char** argv)
{
	// Check that 3 file names have been passed
	if (argc != 4) return ErrorArguments(argc);

	// Declare vectors
	vector<int> vectorRandomOrder;
	vector<int> vectorReversedOrder;
	vector<int> vectorSortedOrder;

	// Create vectors from files
	int error = CreateVectors(argv[1], argv[2], argv[3], vectorRandomOrder, vectorReversedOrder, vectorSortedOrder);
	if (error) return error;

	// Heap sort all vectors and output results
	HeapSortAllVectors(argv[1], argv[2], argv[3], vectorRandomOrder, vectorReversedOrder, vectorSortedOrder);

	return 0;
}

// Heap construcor
Heap::Heap(unsigned int elements)
{
	for (unsigned int i = 0; i < elements; i++) data.push_back(0);
	last = -1;
}

// Insert a new element in the Heap
void Heap::Insert(int newElement, int &comparisons)
{
	// Add newElement to the end of the Heap
	last = last + 1;
	data[last] = newElement;
	if (last == 0) return;

	// Sort Element into Heap
	int childIndex = last, parentIndex = 0;
	bool swapping = true;

	while (swapping == true)
	{
		swapping = false;

		// Check if right child or left child
		if (childIndex % 2 == 0) parentIndex = childIndex / 2 - 1;		// Right child
		else parentIndex = childIndex / 2;								// Left child

		// Check if swapping must occur
		if (parentIndex >= 0)
		{
			if (data[childIndex] > data[parentIndex])
			{
				// Swap data between child and parent
				swap(data[childIndex], data[parentIndex]);
				swapping = true;
				childIndex = parentIndex;
			}
			comparisons++;
		}
	}
}

// Returns the value of the root element of the Heap
int Heap::RootData()
{
	return data[0];
}

// Deletes the root from the Heap
void Heap::DeleteRoot(int &comparisons)
{
	// Check that there are elements in the Heap
	if (last < 0) return;

	// Copy data[last] to data[root]
	data[0] = data[last];

	// Delete data[last]
	data[last] = 0;
	last = last - 1;

	// Fix the Heap
	int parentIndex = 0, leftChildIndex = parentIndex * 2 + 1, rightChildIndex = parentIndex * 2 + 2;
	bool swapping = true;

	while (swapping == true)
	{
		swapping = false;
		int swapChildIndex = 0;

		// Check which child is larger
		if (data[leftChildIndex] > data[rightChildIndex]) swapChildIndex = leftChildIndex;
		else swapChildIndex = rightChildIndex;
		comparisons++;

		// Check if swap child is larger than parent
		if (data[swapChildIndex] > data[parentIndex])
		{
			// Swap child with parent
			swap(data[swapChildIndex], data[parentIndex]);
			parentIndex = swapChildIndex;
			swapping = true;
		}
		comparisons++;

		// Update children
		leftChildIndex = parentIndex * 2 + 1;
		rightChildIndex = parentIndex * 2 + 2;

		// Check if end of Heap
		if (leftChildIndex > last) break;
		else if(rightChildIndex > last)
		{
			// Check if data needs to be swapped
			if (data[leftChildIndex] > data[parentIndex])
			{
				swap(data[leftChildIndex], data[parentIndex]);
			}
			comparisons++;
			break;
		}
	}
}

// Deletes the root from the Heap
void Heap::DeleteRootChanged(int &comparisons)
{
	// Check that there are elements in the Heap
	if (last < 0) return;

	// Copy data[last] to data[root]
	data[0] = data[last];

	// Delete data[last]
	data[last] = 0;
	last --;

	// Fix the Heap
	int parentIndex = 0, leftChildIndex = parentIndex * 2 + 1, rightChildIndex = parentIndex * 2 + 2;
	bool swapping = true;

	// While left child exists
	while (leftChildIndex < last)
	{
		int swapChildIndex = 0;

		// Check if right child exists to find which child to use for swap
		if (rightChildIndex < last)
		{
			// Check which child is larger and increment comparisons
			if (data[leftChildIndex] > data[rightChildIndex]) swapChildIndex = leftChildIndex;
			else swapChildIndex = rightChildIndex;
			comparisons++;
		}
		else swapChildIndex = leftChildIndex;

		// Check if swap should occur (child larger than parent) and increment comparisons
		if (data[swapChildIndex] > data[parentIndex]) swap(data[swapChildIndex], data[parentIndex]);
		comparisons++;

		// Update indices
		parentIndex = swapChildIndex;
		leftChildIndex = parentIndex * 2 + 1;
		rightChildIndex = parentIndex * 2 + 2;
	}
}

// Prints elements of a Heap; should only be called on a full Heap
void Heap::PrintHeap()
{
	for (unsigned int i = 0; i < data.size(); i++) cout << data[i] << ' ';
	cout << endl;
}

// Prints elements of a Vector
void PrintVector(vector<int> vector)
{
	for (unsigned int i = 0; i < vector.size(); i++) cout << vector[i] << ' ';
	cout << endl;
}

// Error: Could not open file
int ErrorFile(char *file)
{
	cout << "Error: Could not open file (" << file << ")" << endl;
	return 2;
}

// Creates a vector from an input file
int CreateVectorFromFile(char *file, vector<int> &vector)
{
	// Open file and check that it opens correctly
	ifstream inFile(file);
	if (!inFile) return ErrorFile(file);

	while (!inFile.eof())
	{
		// Get line from file
		string line;
		getline(inFile, line);

		// Make sure not at end of file
		if (inFile.eof()) break;

		// Convert line to integer and push back to vector
		int number;
		number = stoi(line);
		//cout << number << ' ';	// DEBUG: check that the file can be read
		vector.push_back(number);
	}

	/* DEBUG: check that the array was copied
	cout << endl << "File " << file << ":" << endl;
	for (unsigned int count = 0; count < vector.size(); count++)
	{
		cout << vector[count] << ' ';
	}
	cout << endl;
	/* END DEBUG */

	return 0;
}


// Open files and load numbers into vectors
int CreateVectors(char *fileRandomOrder, char *fileReversedOrder, char *fileSortedOrder, vector<int> &vectorRandomOrder, vector<int> &vectorReversedOrder, vector<int> &vectorSortedOrder)
{
	// Create random order vector
	int error = CreateVectorFromFile(fileRandomOrder, vectorRandomOrder);
	if (error) return error;

	// Create reversed order vector
	error = CreateVectorFromFile(fileReversedOrder, vectorReversedOrder);
	if (error) return error;

	// Create sorted order vector
	error = CreateVectorFromFile(fileSortedOrder, vectorSortedOrder);
	if (error) return error;

	return 0;
}

// Error: Not enough arguments passed to program
int ErrorArguments(int arguments)
{
	cout << "Error: Incorrect number of arguments passed to HeapSort (" << arguments << " arguments passed)" << endl;
	return 1;
}

// Inserts elements from vector into a Heap and deletes elements from Heap, counting comparisons for each
void HeapSort(vector<int> &sortingVector, char *fileName)
{
	Heap heap(sortingVector.size());
	int comparisons = 0;

	// Insert elements into the Heap
	for (unsigned int i = 0; i < sortingVector.size(); i++) heap.Insert(sortingVector[i], comparisons);

	// Print the state of the Heap and the number of comparisons for insertion
	cout << "Heap before sorting: " << fileName << endl;
	heap.PrintHeap();
	cout << "InsertHeap: " << comparisons << " comparisons" << endl;

	// For all elements of the Heap copy the root of the Heap to last index of the sortingVector and delete the root
	comparisons = 0;
	for (int i = sortingVector.size() - 1; i >= 0; i--)
	{
		sortingVector[i] = heap.RootData();
		heap.DeleteRootChanged(comparisons);
	}

	// Print the number of comparisons for deletion and the state of the sortingVector
	cout << "DeleteRoot: " << comparisons << " comparisons" << endl;
	cout << "Vector after sorting:" << endl;
	PrintVector(sortingVector);
}

// Heap sort all vectors and output results
void HeapSortAllVectors(char *fileRandomOrder, char *fileReversedOrder, char *fileSortedOrder, vector<int> &vectorRandomOrder, vector<int> &vectorReversedOrder, vector<int> &vectorSortedOrder)
{
	// Sort random order vector
	HeapSort(vectorRandomOrder, fileRandomOrder);
	cout << endl;

	// Sort reversed order vector
	HeapSort(vectorReversedOrder, fileReversedOrder);
	cout << endl;

	// Sort sorted order vector
	HeapSort(vectorSortedOrder, fileSortedOrder);
}
