//============================================================================
// Name        : MipsDemo.cpp
// Author      : Maoqin Zhu
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Cpu.h"
#include "Memory.h"
#include <fstream>
using namespace std;

int main() {
	cout << "============================================================================\n" << endl;
	cout << "Project 3 Mips Simulator" << endl;
	cout << "Maxy Zhu for ECE 510" << endl;
	cout << "Instructor: Yadi Eslami\n" << endl;
	cout << "============================================================================\n" << endl;

	// Basic Declarations
    Cpu cpu;	// Object from Class CPU
    Memory IMem;	// Instruction memory from Class Memory
    Memory DMem;	// Data memory from Class Memory
    int DMemSize = 4 ;	// the number of DMem address shown on screen(4 is enough in this project)
    int Isize ;	// the number of instructions you load into IMem
    int reg_size ;	// the number of registers displayed on screen


    // Instruction loading
    cout << "Welcome, how many instructions you wanna load into Instruction Memory?(from 1 to 34):" << endl;
    flag1: // error correction for invalid number of instruction
    cin >> Isize;	// 34 in this project
    // error correction
    if (Isize<1 or Isize>34){
    	cout << "Invalid loading! Please select again:" << endl;
    	goto flag1;
    }

    // fstream helps input text file
    char ins[32];
    ifstream infile;
    infile.open("D:/eclipse/eclipseCpp/setup/eclipse/project/MipsDemo/src/Instruction/code.txt");
    for (int i = 0; i < Isize; ++i) {
    	infile >> ins;
        IMem.charToMem(ins, i);
    }
    infile.close();
    cout << endl;

    // Display on screen
    printf("IMem:\n");
    cout << endl;
    IMem.printMem(0, Isize);
    cout << endl;

    printf("Load instructions successfully!\n");
    cout << endl;

    cout << "How many registers you wanna display on screen?(from 1 to 32):" << endl;
    flag2: // error correction for invalid number of registers
    cin >> reg_size;	// 16 in this project

    // error correction
    if (reg_size<1 or reg_size>32){
    	cout << "Invalid input! Please select again:" << endl;
    	goto flag2;
    }


    // Classic 5 stage pipeline
    char continue1;
    char continue2;
    char Back2Mode;

    do {
        Cpu cpu;	// Object from Class CPU
        Memory DMem;	// Data memory from Class Memory

    	// Basic variables for counting utilization
        int u1 = 0;
        int u2 = 0;
        int u3 = 0;
        int u4 = 0;
        int u5 = 0;
        int Usum = 0;
        // Mode choose
        int mode=0;
        cout << "Which mode? instruction mode(1) or cycle mode(2):\n";
        flag3:  // for invalid input of mode
        cin >> mode;

        if (mode == 2) {

        	// Cycle mode
        	int in_cyc = 0 ; // input of cycle number
            int current_cyc = 0; // the number of cycle in current process
            int total_cyc; // the total number of cycle in current process
            continue2_flag:
            current_cyc += in_cyc;
			total_cyc = current_cyc;
            cout << "Select the number of cycles:\n";
            flag4: // error correction for invalid number of cycle
            cin >> in_cyc;
            total_cyc += in_cyc;

            // error correction
            if (in_cyc<0){
            	cout << "Invalid input! Please select again:" << endl;
             	goto flag4;
            }

            for (int i=current_cyc; i < total_cyc; ++i) {
                // implementing parallel execution in specific order
            	printf("\nCycle %02d\n", i + 1);
                u5 += cpu.WB();
                u4 += cpu.MEM(DMem);
                u3 += cpu.EX();
                cpu.hazard_check();
                u2 += cpu.ID();
                u1 += cpu.IF(IMem, Isize);
                Usum++;
                // Display registers and Dmem
                cout << endl;
            	printf("DMem:\n");
                DMem.printMem(0, DMemSize);
                cpu.printReg(reg_size);
            }

            cout << "\nExcellent! Finish specific CPU cycles!" << endl;
            cout << endl;

            // exit or continue current process
            cout << "CPU has finished " << total_cyc << " cycle(s) in total. Continue this process or not?(y/n)" << endl;
            cin >> continue2;
            if(continue2 == 'y'){
                goto continue2_flag;	// continue
            }else{
            	// utilization of each stage and total time(in CPU cycles)
            	cout << endl;
             	printf("Utilization of each stage:\n");
                printf("IF:\t%.2f%%\n",  (double) u1 / Usum * 100.0);
                printf("ID:\t%.2f%%\n",  (double) u2 / Usum * 100.0);
                printf("EX:\t%.2f%%\n",  (double) u3 / Usum * 100.0);
                printf("MEM:\t%.2f%%\n", (double) u4 / Usum * 100.0);
                printf("WB:\t%.2f%%\n",  (double) u5 / Usum * 100.0);
                cout << endl;
                printf("Total time(in CPU cycles): %d\n", Usum);
                cout << endl;
            }

        } else if (mode == 1) {

        	// Instruction mode
        	int in_ins = 0;
            int current_ins = 0;
            int i = 0;
        	continue1_flag1:
            cout << "Select the number of instructions:\n";
            flag5: // error correction for invalid number of instruction
			int total_ins = current_ins;
			cin >> in_ins;
            total_ins += in_ins;

            // error correction
            if (total_ins > Isize or total_ins < 1){
                	cout << "Invalid input! You loaded " << Isize << " instructions into memory at beginning. " << "Please select again:" << endl;
                	goto flag5;
            }

            while (current_ins < total_ins) {

            	// implementing parallel execution in specific order
            	printf("\nCycle %02d\n", ++i);
                u5 += cpu.WB();
                u4 += cpu.MEM(DMem);
                u3 += cpu.EX();
                cpu.hazard_check();
                u2 += cpu.ID();
                u1 += cpu.IF(IMem, Isize);

                Usum++;
                current_ins += cpu.runWB;

                // deal with branch
                if (cpu.branch){
                	current_ins += cpu.skip;
                }

                // only when certain instruction writes back, we display registers and Dmem
                if (cpu.runWB) {
                    cout << endl;
                	printf("DMem:\n");
                    DMem.printMem(0, DMemSize);
                    cpu.printReg(reg_size);
                }
            }

            cout << "\nExcellent! Instructions have been executed successfully!"<<endl;
            cout << endl;

            // exit or continue current process
            cout << "CPU has executed " << total_ins << " instruction(s) in total. Continue this process or not?(y/n)" << endl;
            flag6:   // error correction for invalid instruction number
            cin >> continue1;
            if(continue1 == 'y' and total_ins < 34){
            	goto continue1_flag1;	// continue
            }else if(continue1 == 'y' and total_ins > 34){
                // error correction
            	cout << "Invalid input! You loaded " << Isize << " instructions into memory at beginning. " << "Please select again:" << endl;
            	goto flag6;
            } else {
            // utilization of each stage and total time(in CPU cycles)
            cout << endl;
            printf("Utilization of each stage:\n");
            printf("IF:\t%.2f%%\n",  (double) u1 / Usum * 100.0);
            printf("ID:\t%.2f%%\n",  (double) u2 / Usum * 100.0);
            printf("EX:\t%.2f%%\n",  (double) u3 / Usum * 100.0);
            printf("MEM:\t%.2f%%\n", (double) u4 / Usum * 100.0);
            printf("WB:\t%.2f%%\n",  (double) u5 / Usum * 100.0);
            cout << endl;
            printf("Total time(in CPU cycles): %d\n", Usum);
            cout << endl;
            }

        // error correction
        } else {
        	cout << "Invalid mode! Please select again:" << endl;
        	goto flag3;
        }

        // current process has been finished
        cout << "You have exited! Results are displayed above. Back to select mode again?(y/n)" << endl;
        cin >> Back2Mode;

    } while (Back2Mode == 'y');

    cout << endl;
    cout << "Thank you! Have a nice day!\n" <<endl;

    return 0;
}
