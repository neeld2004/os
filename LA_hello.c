#include <stdio.h>
#include <string.h>

#define MEMORY_SIZE 400  // Total memory size
#define PAGE_SIZE 10     // Page size in words
#define NUM_PAGES (MEMORY_SIZE / PAGE_SIZE) // Number of pages

// Page table entries (these are indices of real pages)
int pageTable[NUM_PAGES] = {11, 23, 5}; // Example page table

// Main memory (simulation of the real memory)
char memory[MEMORY_SIZE][4]; // Memory with each word 4 bytes

// Load the "Welcome" message into memory starting at address 10
void loadWelcomeMessage() {
    strcpy(memory[10], "H");
    strcpy(memory[11], "e");
    strcpy(memory[12], "l");
    strcpy(memory[13], "l");
    strcpy(memory[14], "o");
    strcpy(memory[15], ",");
    strcpy(memory[16], " ");
    strcpy(memory[17], "W");
    strcpy(memory[18], "e");
    strcpy(memory[19], "l");
    strcpy(memory[20], "c");
    strcpy(memory[21], "o");
    strcpy(memory[22], "m");
    strcpy(memory[23], "e");
}

// Function to convert virtual address (VA) to real address using the page table
int convertToRealAddress(int virtualAddress) {
    int pageNum = virtualAddress / PAGE_SIZE;        // Calculate the page number
    int offset = virtualAddress % PAGE_SIZE;         // Calculate the offset within the page

    // Fetch the real page number from the page table
    int realPageNum = pageTable[pageNum];

    // Calculate the real address
    int realAddress = realPageNum * PAGE_SIZE + offset;
    return realAddress;
}

// Function to print the "Welcome" message stored in memory
void printWelcomeMessage() {
    for (int i = 10; i <= 23; i++) {
        printf("%s", memory[i]);
    }
    printf("\n");
}

int main() {
    // Load the welcome message into memory
    loadWelcomeMessage();

    // Example: Convert virtual address VA = 12 to real address
    int virtualAddress = 12;
    int realAddress = convertToRealAddress(virtualAddress);

    // Print the real address
    printf("Virtual Address: %d -> Real Address: %d\n", virtualAddress, realAddress);

    // Print the welcome message
    printWelcomeMessage();

    return 0;
}
