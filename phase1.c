#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char memory[100][4];
char IR[4];
char R[4];
int IC, SI;
bool toggle;

FILE *input, *output;

void init() {
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 4; j++)
            memory[i][j] = ' ';
    for (int i = 0; i < 4; i++) {
        IR[i] = ' ';
        R[i] = ' ';
    }
}

void printMemory() {
    printf("\nMemory Map:\n");
    for (int i = 0; i < 100; i++) {
        int hasChar = 0;
        for (int j = 0; j < 4; j++)
            if (memory[i][j] != ' ') hasChar = 1;

        printf("%02d: ", i);
        for (int j = 0; j < 4; j++) {
            if (memory[i][j] == ' ' && hasChar)
                printf("  ");
            else if (memory[i][j] == ' ')
                printf("* ");
            else
                printf("%c ", memory[i][j]);
        }
        printf("\n");
    }
}

void endWhile() {
    printf("Job ended.\n");
}

void MOS() {
    if (SI == 1) {
        char buffer[41];
        fgets(buffer, 41, input);
        int k = 0;
        int add = (IR[2] - '0') * 10 + (IR[3] - '0');
        for (int i = 0; i < strlen(buffer) && i < 40; i++) {
            memory[add][k++] = buffer[i];
            if (k == 4) {
                k = 0;
                add++;
            }
        }
    } else if (SI == 2) {
        int add = (IR[2] - '0') * 10 + (IR[3] - '0');
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 4; j++) {
                fputc(memory[add][j], output);
            }
            add++;
        }
        fputc('\n', output);
    } else if (SI == 3) {
        fputc('\n', output);
    }
}

void ExecuteUserProgram() {
    int I = 0;
    while (1) {
        for (int i = 0; i < 4; i++)
            IR[i] = memory[I][i];
        I++;

        if (IR[0] == 'G' && IR[1] == 'D') {
            SI = 1; MOS();
        } else if (IR[0] == 'P' && IR[1] == 'D') {
            SI = 2; MOS();
        } else if (IR[0] == 'L' && IR[1] == 'R') {
            int add = (IR[2] - '0') * 10 + (IR[3] - '0');
            for (int i = 0; i < 4; i++)
                R[i] = memory[add][i];
        } else if (IR[0] == 'S' && IR[1] == 'R') {
            int add = (IR[2] - '0') * 10 + (IR[3] - '0');
            for (int i = 0; i < 4; i++)
                memory[add][i] = R[i];
        } else if (IR[0] == 'C' && IR[1] == 'R') {
            int add = (IR[2] - '0') * 10 + (IR[3] - '0');
            toggle = true;
            for (int i = 0; i < 4; i++) {
                if (R[i] != memory[add][i])
                    toggle = false;
            }
        } else if (IR[0] == 'B' && IR[1] == 'T') {
            int add = (IR[2] - '0') * 10 + (IR[3] - '0');
            if (toggle)
                I = add;
        } else if (IR[0] == 'H') {
            SI = 3; MOS(); break;
        }
    }
}

void Load() {
    char buffer[100];
    int block = 0;
    while (fgets(buffer, sizeof(buffer), input)) {
        if (strncmp(buffer, "$AMJ", 4) == 0) {
            printf("\nProcessing new job\n");
            block = 0;
            init();
        } else if (strncmp(buffer, "$DTA", 4) == 0) {
            ExecuteUserProgram();
        } else if (strncmp(buffer, "$END", 4) == 0) {
            endWhile();
            printMemory();
        } else {
            if (block > 100) {
                printf("Out of memory.\n");
            } else {
                int k = 0;
                for (int i = block; i < block + 10 && k < strlen(buffer); i++) {
                    for (int j = 0; j < 4 && k < strlen(buffer); j++) {
                        memory[i][j] = buffer[k++];
                        if (memory[i][j] == 'H') break;
                    }
                }
                block += 10;
            }
        }
    }
    printf("\nAll jobs processed\n");
}

int main() {
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    if (!input || !output) {
        printf("Error opening file.\n");
        return 1;
    }
    Load();
    fclose(input);
    fclose(output);
    return 0;
}
