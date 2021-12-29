#include "Cpu.h"

int Cpu::MEM(Memory &mem) {

    int exe = 0;

    if (done4) {
    	// basic setup
        printf("Instruction %02d current stage: MEM\n", insNum4 / 4 + 1);
        done4 = false;
        done5 = true;

        long long n = array2Int(ALU_result, 31, 0); // result of ALU

        // MemWrite control signal
        if (MemWrite34) {
            exe = 1;
            mem.intToMem(data2_34, n);
        }

        // MemRead control signal
        if (MemRead34) {
            exe = 1;
            mem.loadMem(n, ReadData);
        }

        // update the latch value in MEM/WB pipeline register
        MemToReg45 = MemToReg34;
        RegWrite45 = RegWrite34;
        copyArray(ALU_result, ALU_result45, 0, 0, 32);
        RegDst45 = RegDst34;
        insNum5 = insNum4;

        // mul operation
        if (mul34) {
            mul45 = true;
            copyArray(highbits34, highbits45, 0, 0, 32);
            mul34 = false;
        }
    }
    return exe;
}
