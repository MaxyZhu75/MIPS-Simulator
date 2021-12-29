#include <iostream>

#ifndef _METHODS_H_
#define _METHODS_H_

// declare some basic methods to help program built

void addArray(int a[], int b[], int c[], int len);

void subArray(int a[], int b[], int c[], int len);

void andArray(int a[], int b[], int c[], int len);

void orArray(int a[], int b[], int c[], int len);

int  addArrayMul(int a[], int b[], int c[], int begin, int len);	// help mul operation

void mulArray(int a[], int b[], int c[], int highbits[], int len);

void hexArray(int a[],int size);

void printArray(int a[], int begin, int end);

void copyArray(int a[], int b[], int begin1, int begin2, int len);

long long array2Int(int a[], int begin, int end);

void shiftL(int a[], int b[], int len, int shamt);

void shiftRL(int a[], int b[], int len, int shamt);		// logic shift

void ALUOpS(int op);	// display the name of instruction

#endif //_METHODS_H_
