#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

char memory[200][4];   // 200 words of memory, each 4 bytes
char IR[4];            // Instruction Register
char R[4];             // General Purpose Register
int IC = 0;            // Instruction Counter
bool C = false;        // Toggle Register

// Print error and exit
void printError(const char *msg) {
    printf("ERROR: %s at instruction %d: %.4s\n", msg, IC - 1, IR);
    exit(1);
}

// Simulated OS function (only H implemented here)
void MOS(int SI) {
    if (SI == 3) {
        printf("Program Halted Normally.\n");
        exit(0);
    }
}

// Load a test program with both opcode and operand errors
void loadProgramWithErrors() {
    // Valid instructions
    memcpy(memory[0], "LR10", 4);  // Load from 10
    memcpy(memory[1], "CR10", 4);  // Compare with 10

    // ❌ Invalid opcode (not among defined ones)
    memcpy(memory[2], "ZZ99", 4);

    // ❌ Operand out of bounds (e.g., address 205 is beyond memory limit 199)
    memcpy(memory[3], "SR205", 4); // Only first 4 bytes copied, operand will be read as 20

    // Valid halt instruction
    memcpy(memory[4], "H   ", 4);

    // Dummy memory content at location 10
    memcpy(memory[10], "1234", 4);
}

// Executes the loaded program
void executeProgram() {
    while (1) {
        memcpy(IR, memory[IC], 4);  // Fetch
        IC++;                       // Increment instruction counter

        char op[3] = {IR[0], IR[1], '\0'};  // Extract opcode
        int operand = (IR[2] - '0') * 10 + (IR[3] - '0');  // Decode operand

        // Validate operand range if not halt
        if (strcmp(op, "H") != 0 && (operand < 0 || operand >= 200)) {
            printError("Operand out of memory bounds");
        }

        // Instruction execution
        if (strcmp(op, "LR") == 0) {
            memcpy(R, memory[operand], 4);
        } else if (strcmp(op, "SR") == 0) {
            memcpy(memory[operand], R, 4);
        } else if (strcmp(op, "CR") == 0) {
            C = (memcmp(R, memory[operand], 4) == 0);
        } else if (strcmp(op, "BT") == 0) {
            if (C) IC = operand;
        } else if (strcmp(op, "GD") == 0 || strcmp(op, "PD") == 0) {
            // Skipped I/O simulation
        } else if (strcmp(op, "H") == 0) {
            MOS(3);
        } else {
            printError("Invalid opcode");
        }
    }
}

// Main function
int main() {
    loadProgramWithErrors();
    printf("Executing Program...\n");
    executeProgram();
    return 0;
}
