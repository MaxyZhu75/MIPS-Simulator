#include "Cpu.h"

int Cpu::IF(Memory mem, int size) {

    int exe = 0;

    if (runIF) {

        if (nop == false) {		// check if stops and waits

        	branch = 0;
            
        	//  According to control signal PCSrc, check if there is a branch
            if (PCSrc) {
                pc = pc34;
                PCSrc = 0;
                branch = 1;
            }
            
            
            //  Only 34 instructions in this project
            if (pc / 4 + 1 <= 34) {
                printf("Instruction %02d current stage: IF\n", pc / 4 + 1);
                exe = 1;
                done2 = true;
            } else {
                done2 = false;
                runIF = false;
            }


            // store the value of PC to IR
            mem.loadMem(pc, IR);

            // update the latch value in IF/ID pipeline register
            insNum2 = pc;
            pc12 = pc + 4;

            // point to the address of next instruction executed
            pc = pc + 4;
        }
    }
    
    
    runID_check = true;

    // indicates that this stage is being used at certain clock
    return exe;
}
