#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Heap class with functions specific to finding the number of comparisons when using Heap Sort method
class Heap
{
private:
	vector<int> data;
	int last;

public:
	Heap(unsigned int elements);
	~Heap() { };
	void Insert(int newElement, int &comparisons);
	int RootData();
	void DeleteRoot(int &comparisons);
	void DeleteRootChanged(int &comparisons);
	void PrintHeap();
};


void PrintVector(vector<int> vector);                                           // Prints elements of a Vector
int ErrorFile(char *file);                                                      // Error: Could not open file
int CreateVectorFromFile(char *file, vector<int> &vector);                      // Creates a vector from an input file
int CreateVectors(char *fileRandomOrder, char *fileReversedOrder, char *fileSortedOrder, vector<int> &vectorRandomOrder, vector<int> &vectorReversedOrder, vector<int> &vectorSortedOrder); // Open files and load numbers into vectors
int ErrorArguments(int arguments);                                              // Error: Not enough arguments passed to program
void HeapSort(vector<int> &sortingVector, char *fileName);                      // Inserts elements from vector into a Heap and deletes elements from Heap, counting comparisons for each
void HeapSortAllVectors(char *fileRandomOrder, char *fileReversedOrder, char *fileSortedOrder, vector<int> &vectorRandomOrder, vector<int> &vectorReversedOrder, vector<int> &vectorSortedOrder);   // Heap sort all vectors and output results
