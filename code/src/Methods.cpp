#include "Methods.h"

// define the functions in header file

void addArray(int a[], int b[], int c[], int len) {
    int carry = 0, sum;
    for (int i = 0; i < len; ++i) {
        sum = a[i] + b[i] + carry;
        switch (sum) {
            case 0:
                c[i] = 0;
                carry = 0;
                break;
            case 1:
                c[i] = 1;
                carry = 0;
                break;
            case 2:
                c[i] = 0;
                carry = 1;
                break;
            case 3:
                c[i] = 1;
                carry = 1;
                break;
        }
    }
}

void subArray(int a[], int b[], int c[], int len) {
    int borrow = 0, diff;
    for (int i = 0; i < len; ++i) {
        diff = a[i] - b[i] - borrow;
        switch (diff) {
            case 1:
                c[i] = 1;
                borrow = 0;
                break;
            case 0:
                c[i] = 0;
                borrow = 0;
                break;
            case -1:
                c[i] = 1;
                borrow = 1;
                break;
            case -2:
                c[i] = 0;
                borrow = 1;
                break;
        }
    }
}

void andArray(int a[], int b[], int c[], int len) {
    for (int i = 0; i < len; ++i) {
        if (a[i] and b[i]) c[i] = 1;
        else c[i] = 0;
    }
}

void orArray(int a[], int b[], int c[], int len) {
    for (int i = 0; i < len; ++i) {
        if (a[i] or b[i]) c[i] = 1;
        else c[i] = 0;
    }
}

int addArrayMul(int a[], int b[], int c[], int bgein, int len) {	// help mul operation
    int carry = 0;
    int sum;
    for (int i = 0; i < len; ++i) {
        sum = a[i] + b[i + bgein] + carry;
        switch (sum) {
            case 0:
                c[i + bgein] = 0;
                carry = 0;
                break;
            case 1:
                c[i + bgein] = 1;
                carry = 0;
                break;
            case 2:
                c[i + bgein] = 0;
                carry = 1;
                break;
            case 3:
                c[i + bgein] = 1;
                carry = 1;
                break;
        }
    }
    if (bgein + len <= 63) {
        c[bgein + len] = carry;
    }
    return carry;
}

void mulArray(int a[], int b[], int c[], int highbits[], int len) {
    int ans[64] = {0};
    int carry = 0;
    for (int i = 0; i < len; ++i) {
        if (b[i] == 1) {
            addArrayMul(a, ans, ans, i, len);
        }
    }
    copyArray(ans, c, 0, 0, len);
    copyArray(ans, highbits, len, 0, len);
}

void hexArray(int a[], int len) {
    char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    for (int i = len - 1; i >= 3; i = i - 4) {
        printf("%c", hex[array2Int(a, i, i - 3)]);
    }
}

void printArray(int a[], int begin, int end) {
    for (int i = begin; i >= end; --i) {
        printf("%d", a[i]);
    }
}

void copyArray(int a[], int b[], int begin1, int begin2, int len) {
    for (int i = 0; i < len; ++i) {
        b[i + begin2] = a[i + begin1];
    }
}

long long array2Int(int a[], int begin, int end) {
    long long ans = 0;
    for (int i = begin; i >= end; i--) {
        ans = ans * 2 + a[i];
    }
    return ans;
}

void shiftL(int a[], int b[], int len, int shamt) {
    int i;
    for (i = len - 1; i - shamt >= 0; --i) {
        b[i] = a[i - shamt];
    }
    for (; i >= 0; --i) {
        b[i] = 0;
    }
}

void shiftRL(int a[], int b[], int len, int shamt) {		// logic shift
    int i;
    for (i = 0; i + shamt < len; ++i) {
        b[i] = a[i + shamt];
    }
    for (; i < len; ++i) {
        b[i] = 0;
    }
}

void ALUOpS(int op) {	// display the name of instruction

	switch (op) {

    	//R-type
    	case 0: //sll
        	printf("sll");
        	break;
    	case 2: //srl
    		printf("srl");
        	break;
    	case 24://mul
    		printf("mul");
        	break;
        case 32://add
            printf("add");
            break;
        case 34://sub
            printf("sub");
            break;
        case 36://and
            printf("and");
            break;
        case 37://or
            printf("or");
            break;

        //I-type
        case 400://beq
            printf("beq");
            break;
        case 800://addi
            printf("addi");
            break;
        case 1000://slti
            printf("slti");
            break;
        case 1100://sltiu
            printf("sltiu");
            break;
        case 1200://andi
            printf("andi");
            break;
        case 1300://ori
            printf("ori");
            break;
        case 1500://lui
            printf("lui");
            break;
        case 3500://lw
            printf("lw");
            break;
        case 4300://sw
            printf("sw");
            break;
        default:
            printf("error");
            break;
    }
}
