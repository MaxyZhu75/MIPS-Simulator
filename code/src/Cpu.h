#include "Methods.h"
#include "Memory.h"

#ifndef _CPU_H_
#define _CPU_H_

class Cpu {
public:
	// Necessary flag signals declaration
	bool nop;				// nop
    bool runID_check;    	// after stage IF
    int	 branch;	   		// if there is a branch
    int	 skip;	   			// the number of instructions been skipped by branch
    bool runIF;    			// record and control fetching operation
    int  runWB;	  		 	// record and control writing back operation
    // flag signals judging the execution of each stage in order
    bool done2;
    bool done3;
    bool done4;
    bool done5;
    
    
    
    // 32 registers and an array signaling the register is available or not
    int Reg[32][32];
    int regBusy[32];
    // PC
    int pc;
    // IR
    int IR[32];
    


    // All Control signals!
    int PCSrc;    		
    int ALUSrc;  		
    int ALUOp;
    int RegDst;	
    int MemWrite;	
    int MemRead;		
    int MemToReg;		
    int RegWrite;		
    
    

    // IF/ID pipeline registers
    int pc12;
    // helps represent the number of current executed instruction for next stage
    int insNum2;
    
    
    
    // ID/EX pipeline registers
    int pc23;
    int IR23[32];
    int data1[32]; 		// Read data 1
    int data2[32]; 		// Read data 2
    int imm32[32];		// offset for Branch choose or ALU
    // helps represent the number of current executed instruction for next stage
    int insNum3 = 0;
  
    

    // EX/MEM pipeline registers
    int ALU_result[32];
    // Latch values in this stage
    int pc34;
    int data2_34[32];		// receives from Read data 2
    int RegDst34;
    int MemWrite34;
    int MemRead34;
    int MemToReg34;
    int RegWrite34;
    // helps represent the number of current executed instruction for next stage
    int insNum4;
    
    
    
    // MEM/WB pipeline registers
    int ReadData[32];		 // Read data
    // Latch value in this stage
    int RegDst45;			 // receives from RegDest
    int ALU_result45[32];    // receives offset(immediate) from ALU
    int MemToReg45;
    int RegWrite45;
    // helps represent the number of current executed instruction for next stage
    int insNum5;
    
    
    
    // Latch value for mul
    bool mul34;
    bool mul45;
    int  highbits34[32];
    int  highbits45[32];

    
    
    //  Member Functions
   
    // defined in Cpu_unit
    void printReg(int reg_size); 	// print out the register content, control signals and latch values
    Cpu();							// initialize basic variables from header files
    
    // defined in IF
    int  IF(Memory mem1, int size);
   
    // defined in ID
    int  hazard_check();
    int  ID();

    // defined in EX
    int  EX();
    void ALU(int data1[], int data2[], int ALUOp);

    // defined in MEM
    int  MEM(Memory &mem2);
    
    // defined in WB
    int  WB();

};

#endif //_CPU_H_
