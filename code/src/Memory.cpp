#include "Memory.h"

// defined the member functions in herder file

void Memory::loadMem(int addr, int a[]) {
    copyArray(Mem[addr + 0], a, 0, 24, 8);
    copyArray(Mem[addr + 1], a, 0, 16, 8);
    copyArray(Mem[addr + 2], a, 0, 8, 8);
    copyArray(Mem[addr + 3], a, 0, 0, 8);
}

void Memory::printMem(int begin, int len) {
    printf("MemAdress\t\t     ");
    printf("Binary\t\t     ");
    printf("Hex\n");
	for (int i = begin; i < len; ++i) {
        printf("0x");
        printf("%08x:\t", 4 * i);

        printArray(Mem[4 * i + 0], 7, 0);
        printArray(Mem[4 * i + 1], 7, 0);
        printArray(Mem[4 * i + 2], 7, 0);
        printArray(Mem[4 * i + 3], 7, 0);

        printf("  0x");
        hexArray(Mem[4 * i + 0], 8);
        hexArray(Mem[4 * i + 1], 8);
        hexArray(Mem[4 * i + 2], 8);
        hexArray(Mem[4 * i + 3], 8);

        printf("\n");
    }
}

void Memory::charToMem(char b[], int len) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 8; ++j) {
            Mem[4 * len + i][j] = b[(i + 1) * 8 - 1 - j] - '0';
        }
    }
}

void Memory::intToMem(int c[], int len) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 8; ++j) {
            Mem[len + i][j] = c[(3 - i) * 8 + j];
        }
    }
}
