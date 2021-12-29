#include "Cpu.h"

int Cpu::WB() {

    int exe = 0;
    runWB = 0;

    if (done5) {
    	// basic setup
        printf("Instruction %02d current stage: WB", insNum5 / 4 + 1);
        done5 = false;
        runWB = 1;
        printf("\t(for Instruction %02d, RegWrite in MEM/WB pipeline register is %d) ", insNum5 / 4 + 1, RegWrite45);

        // according to the function of control signal
        if (RegWrite45) {
            exe = 1;
            if (MemToReg45) {
                copyArray(ReadData, Reg[RegDst45], 0, 0, 32);
            } else {
                copyArray(ALU_result45, Reg[RegDst45], 0, 0, 32);
            }
            regBusy[RegDst45] = 0;
            printf("Writing finished! Thus, R%d is available!", RegDst45);
        }
        printf("\n");

        // mul operation
        if (mul45) {
            copyArray(highbits45, Reg[RegDst45 + 1], 0, 0, 32);
            mul45 = false;
        }
    }
    return exe;
}

// print out the register content, control signals and latch values
void Cpu::printReg(int reg_size) {
    printf("\n");
	printf("Registers:\n");
    printf("R");
    printf("\t          Binary");
    printf("\t          Hex\n");
	for (int i = 0; i < reg_size; ++i) {
        printf("%02d:  ", i);
        printArray(Reg[i], 31, 0);
        printf("  0x");
        hexArray(Reg[i], 32);
        printf("  \n");
	}
	printf("\n");
	printf("PC:\t\t%d", pc);
	printf("\n");
	printf("IR:\t\t");
	printArray(IR, 31, 0);
	printf("\n");
	printf("Immediate:\t");
	printArray(imm32, 31, 0);
	printf("\n");
	printf("ReadData1:\t");
	printArray(data1, 31, 0);
	printf("\n");
	printf("ReadData2:\t");
	printArray(data2, 31, 0);
	printf("\n");
	printf("ALUResult:\t");
	printArray(ALU_result, 31, 0);
	printf("\n");
	printf("\n");
	printf("Control Signals:");
	printf("\n");
	printf("PCSrc:\t\t%d", PCSrc);
	printf("\n");
	printf("RegWrite:\t%d", RegWrite);
	printf("\n");
	printf("ALUSrc:\t\t%d", ALUSrc);
	printf("\n");
	printf("ALUOp:\t\t");
	ALUOpS(ALUOp);
	printf("\n");
	printf("RegDst:\t\t%d", RegDst);
	printf("\n");
	printf("MemWrite:\t%d", MemWrite);
	printf("\n");
	printf("MemRead:\t%d", MemRead);
	printf("\n");
	printf("MemToReg:\t%d", MemToReg);
	printf("\n");
}
