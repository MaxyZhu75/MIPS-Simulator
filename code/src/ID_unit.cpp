#include "Cpu.h"

// sign extend module
void signExtend(int imm[], int imm32[], int sign, int flag) {
    for (int i = 0; i <= 15; ++i) {
        imm32[i] = imm[i];
    }
    for (int i = 16; i < 32; ++i) {
        if (flag == 1) {
            imm32[i] = sign;
        } else {
            imm32[i] = 0;
        }
    }
}


// hazard check module
int Cpu::hazard_check() {

    nop = false; 		//  Initialize nop variable

    if (runID_check) {

    	if((insNum2 / 4 + 1) <= 34){

    		printf("Instruction %02d hazard checking...\t", insNum2 / 4 + 1);
			// Data hazard check process
			int rs = array2Int(IR, 25, 21);
			int rt = array2Int(IR, 20, 16);

			printf("(rs: R%d & rt: R%d) ", rs, rt);

			if(regBusy[rs]){
				printf("Currently R%d is unavailable",rs);
			}else{
				printf("Currently R%d is available",rs);
			}

			if(rs!=rt){
				if(regBusy[rt]){
					printf(" and R%d is unavailable",rt);
				}else{
					printf(" and R%d is available",rt);
				}
			}
			printf("!\n");

			if (regBusy[rs] != 0 or regBusy[rt] != 0) {
				  printf("Data Hazard!\n");
				  nop = true;
				  return 1;
				}


        	// Control hazard check process
        	if (runIF) {
        		int op = array2Int(IR, 31, 26);
            	// detect branch by opcode
            	if (op == 4) {
            		printf("Control Hazard!\n");
                	runIF = false;
                	return 2;
            	}
        	} else {
        		runIF = true;
        	}

    	}


    	// No hazards
        printf("No hazards!\n");
        return 0;
    }
    return 0;
}



int Cpu::ID() {

    int exe = 0;

    if (done2) {

        if (nop == false) {
        	// basic setup
            printf("Instruction %02d current stage: ID\n", insNum2 / 4 + 1);
            done2 = false;
            done3 = true;
            exe = 1;
            int signExtendFlag = 0;
            int op = array2Int(IR, 31, 26);
            int rs = array2Int(IR, 25, 21);
            int rt = array2Int(IR, 20, 16);

            // according to the opcode, update the control signals
            switch (op) {
            	// R-type
                case 0:
                    ALUSrc = 0;
                    ALUOp = array2Int(IR, 5, 0);
                    RegDst = 1;
                    MemWrite = 0;
                    MemRead = 0;
                    MemToReg = 0;
                    RegWrite = 1;
                    break;
                // I-type
                case 8:     // addi
                case 10:    // slti
                    ALUSrc = 1;
                    ALUOp = op * 100;
                    RegDst = 0;
                    MemWrite = 0;
                    MemRead = 0;
                    MemToReg = 0;
                    RegWrite = 1;

                    signExtendFlag = 1;
                    break;
                case 12:   	 // andi
                case 13:     // ori
                case 15:   	 // lui
                case 11:   	 // sltiu
                    ALUSrc = 1;
                    ALUOp = op * 100;
                    RegDst = 0;
                    MemWrite = 0;
                    MemRead = 0;
                    MemToReg = 0;
                    RegWrite = 1;
                    break;
                case 35:      //lw
                    ALUSrc = 1;
                    ALUOp = op * 100;
                    RegDst = 0;
                    MemWrite = 0;
                    MemRead = 1;
                    MemToReg = 1;
                    RegWrite = 1;

                    signExtendFlag = 1;
                    break;
                case 43:   	   //sw
                    ALUSrc = 1;
                    ALUOp = op * 100;
                    RegDst;
                    MemWrite = 1;
                    MemRead = 0;
                    MemToReg;
                    RegWrite = 0;

                    signExtendFlag = 1;
                    break;
                case 4:        //beq
                    ALUSrc = 0;
                    ALUOp = op * 100;
                    RegDst;
                    MemWrite = 0;
                    MemRead = 0;
                    MemToReg;
                    RegWrite = 0;

                    signExtendFlag = 1;
                    break;
            }

            // update the latch value in ID/EX pipeline register
            copyArray(Reg[rs], data1, 0, 0, 32);
            copyArray(Reg[rt], data2, 0, 0, 32);
            signExtend(IR, imm32, IR[15], signExtendFlag);
            pc23 = pc12;
            copyArray(IR, IR23, 0, 0, 32);
            insNum3 = insNum2;
        }
    }
    return exe;
}
