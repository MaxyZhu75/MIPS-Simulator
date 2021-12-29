#include "Cpu.h"

// ALU unit
void Cpu::ALU(int data1[], int data2[], int ALUOp) {

	PCSrc = 0;
    switch (ALUOp) {             // according to ALUOp control signal
    	// R-type instruction
        case 0: //sll
            shiftL(data2, ALU_result, 32, array2Int(IR23, 10, 6));
            break;
        case 2: //srl
            shiftRL(data2, ALU_result, 32, array2Int(IR23, 10, 6));
            break;
        case 24://mul
            mul34 = true;
            mulArray(data1, data2, ALU_result, highbits34, 32);
            break;    
        case 32://add
            addArray(data1, data2, ALU_result, 32);
            break;
        case 34://sub
            subArray(data1, data2, ALU_result, 32);
            break;
        case 36://and
            andArray(data1, data2, ALU_result, 32);
            break;
        case 37://or
            orArray(data1, data2, ALU_result, 32);
            break;

        // I-type instruction
        case 400://beq
            if ((int) array2Int(data1, 31, 0) == (int) array2Int(data2, 31, 0))
                PCSrc = 1;
            break;
        case 800://addi
            addArray(data1, data2, ALU_result, 32);
            break;
        case 1000://slti
            copyArray(Reg[0], ALU_result, 0, 0, 32);
            if ((int) (array2Int(data1, 31, 0) - array2Int(imm32, 32, 0)) < 0) {
                ALU_result[0] = 1;
            }
            break;
        case 1100://sltiu
            copyArray(Reg[0], ALU_result, 0, 0, 32);
            if ((int) (array2Int(data1, 31, 0) - array2Int(imm32, 32, 0)) < 0) {
                ALU_result[0] = 1;
            }
            break;
        case 1200://andi
            andArray(data1, data2, ALU_result, 32);
            break;
        case 1300://ori
            orArray(data1, data2, ALU_result, 32);
            break;
        case 1500://lui
            copyArray(imm32, ALU_result, 0, 16, 16);
            copyArray(Reg[0], ALU_result, 0, 0, 16);
            break;
        case 3500://lw
        case 4300://sw
            addArray(data1, data2, ALU_result, 32);
            break;
    }
}



int Cpu::EX() {

    int exe = 0;

    if (done3) {
    	// basic setup
        printf("Instruction %02d current stage: EX", insNum3 / 4 + 1);
        done3 = false;
        done4 = true;
        exe = 1;

        // deal with branch
        pc34 = pc23 + array2Int(imm32, 31, 0) * 4;
    	skip = array2Int(imm32, 31, 0);

        // ALUSrc control signals
        if (!ALUSrc) {
            ALU(data1, data2, ALUOp);
        } else {
            ALU(data1, imm32, ALUOp);
        }

        // RegDst control signals
        if (!RegDst) {
            RegDst34 = array2Int(IR23, 20, 16);
        } else {
            RegDst34 = array2Int(IR23, 15, 11);
        }

        // RegWrite control signals
        if (RegWrite) {

            printf("\t(R%d is being used!)", RegDst34);

            regBusy[RegDst34] = 2;
        }

        printf("\n");

        // update the latch value in EX/MEM pipeline register
        copyArray(data2, data2_34, 0, 0, 32);
        MemWrite34 = MemWrite;
        MemRead34 = MemRead;
        MemToReg34 = MemToReg;
        RegWrite34 = RegWrite;
        insNum4 = insNum3;
    }
    return exe;
}
