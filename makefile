HeapSort.exe	:	HeapSort.o
	g++ HeapSort.o -std=c++11 -o HeapSort.exe

HeapSort.o	:	HeapSort.cpp HeapSort.h
	g++ -std=c++11 -c HeapSort.cpp
	