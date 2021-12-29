#include "Methods.h"

#ifndef _MEMORY_H_
#define _MEMORY_H_

class Memory {
public:
    // IMem and DMem
	int Mem[40 * 4][8]={0};

    // Member functions
    void loadMem(int addr, int a[]);

    void printMem(int begin, int len);

    void charToMem(char b[], int len);

    void intToMem(int c[], int len);

};

#endif //_MEMORY_H_
