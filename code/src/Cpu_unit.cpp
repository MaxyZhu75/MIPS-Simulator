#include "Cpu.h"
#include <cstdio>

// initialize basic variables from header files
Cpu::Cpu() {
	
	// Necessary flag signals declaration
	nop = false;			// nop
    runID_check = false;    // after stage IF
    branch = 0;				// if there is a branch
    skip = 0;				// the number of instructions been skipped by branch
    runIF = true;   		// record and control fetching operation
    runWB = 0;	   			// record and control writing back operation
    // flag signals judging the execution of each stage in order
    done2 = false;
    done3 = false;
    done4 = false;
    done5 = false;

    
    
    // 32 registers and an array signaling the register is available or not
    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 32; ++j) {
            Reg[i][j] = 0;
        }
    }

    for (int i = 0; i < 32; ++i) {
        regBusy[i] = 0;
    }

    // PC
    pc = 0;
    // IR
    for (int i = 0; i < 32; ++i) {
        IR[i] = 0;
    }
    

    
    // All Control signals!
    PCSrc = 0;
    ALUSrc = 0;
    ALUOp = 9999;
    RegDst = 0;
    MemWrite = 0;
    MemRead = 0;
    MemToReg = 0;
    RegWrite = 0;
    

    
    // IF/ID pipeline registers
    pc12;
    // helps represent the number of current executed instruction for next stage
    insNum2 = 0;

    

    // ID/EX pipeline registers
    pc23;
    IR23[32];
    for (int i = 0; i < 32; ++i) {		
        data1[i] = 0;
        data2[i] = 0;
        imm32[i] = 0;
    }    
    // helps represent the number of current executed instruction for next stage
    insNum3 = 0;
    
    
    
    // EX/MEM pipeline registers
    pc34;
    // Latch values in this stage
    data2_34[32];
    for (int i = 0; i < 32; ++i) {
        ALU_result[i] = 0;
    }
    RegDst34;
    MemWrite34 = 0;
    MemRead34 = 0;
    MemToReg34 = 0;
    RegWrite34 = 0;
    // helps represent the number of current executed instruction for next stage
    insNum4 = 0;
    
    
    
    // MEM/WB pipeline registers
    ReadData[32];
    // Latch values in this stage
    RegDst45;
    ALU_result45[32];
    MemToReg45;
    RegWrite45 = 0;
    // helps represent the number of current executed instruction for next stage
    insNum5 = 0;

    
    
    // Latch value for mul
    mul34 = false;
    mul45 = false;
    for (int i = 0; i < 32; ++i) {
        highbits34[i] = 0;
        highbits45[i] = 0;
    }
}
