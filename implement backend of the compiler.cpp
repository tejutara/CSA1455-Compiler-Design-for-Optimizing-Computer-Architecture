#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IR_SIZE 100

// Define stack structure
#define STACK_SIZE 100
int stack[STACK_SIZE];
int top = -1;

// Function to push a value onto the stack
void push(int value) {
    if (top >= STACK_SIZE - 1) {
        fprintf(stderr, "Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack[++top] = value;
}

// Function to pop a value from the stack
int pop() {
    if (top < 0) {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack[top--];
}

// Function to generate assembly code for the given IR
void generateCode(char *ir[]) {
    int i = 0;
    while (ir[i] != NULL) {
        if (isdigit(ir[i][0])) {
            push(atoi(ir[i]));
        } else if (strcmp(ir[i], "+") == 0) {
            int operand2 = pop();
            int operand1 = pop();
            printf("ADD %d, %d\n", operand1, operand2);
            push(operand1 + operand2);
        } else if (strcmp(ir[i], "-") == 0) {
            int operand2 = pop();
            int operand1 = pop();
            printf("SUB %d, %d\n", operand1, operand2);
            push(operand1 - operand2);
        } else if (strcmp(ir[i], "*") == 0) {
            int operand2 = pop();
            int operand1 = pop();
            printf("MUL %d, %d\n", operand1, operand2);
            push(operand1 * operand2);
        } else if (strcmp(ir[i], "/") == 0) {
            int operand2 = pop();
            int operand1 = pop();
            printf("DIV %d, %d\n", operand1, operand2);
            push(operand1 / operand2);
        }
        i++;
    }
}

int main() {
    // Example IR (Postfix notation)
    char *ir[MAX_IR_SIZE] = {"5", "2", "*", "3", "+", "4", "/" , NULL};

    // Generate code
    printf("Generated Assembly Code:\n");
    generateCode(ir);

    return 0;
}

