#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Function prototypes
int expression();
int term();
int factor();

// Global variables
char *input;
char lookahead;

// Error function
void error() {
    fprintf(stderr, "Syntax error\n");
    exit(1);
}

// Function to advance to the next token
void nextToken() {
    lookahead = *input++;
}

// Function to parse an integer
int number() {
    int result = 0;
    while (isdigit(lookahead)) {
        result = result * 10 + (lookahead - '0');
        nextToken();
    }
    return result;
}

// Function to parse a factor
int factor() {
    int result;
    if (lookahead == '(') {
        nextToken();
        result = expression();
        if (lookahead != ')') {
            error();
        }
        nextToken();
    } else if (isdigit(lookahead)) {
        result = number();
    } else {
        error();
    }
    return result;
}

// Function to parse a term
int term() {
    int result = factor();
    while (lookahead == '*' || lookahead == '/') {
        char op = lookahead;
        nextToken();
        if (op == '*') {
            result *= factor();
        } else {
            int divisor = factor();
            if (divisor == 0) {
                fprintf(stderr, "Division by zero\n");
                exit(1);
            }
            result /= divisor;
        }
    }
    return result;
}

// Function to parse an expression
int expression() {
    int result = term();
    while (lookahead == '+' || lookahead == '-') {
        char op = lookahead;
        nextToken();
        if (op == '+') {
            result += term();
        } else {
            result -= term();
        }
    }
    return result;
}

int main() {
    printf("Enter an arithmetic expression: ");
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    input = buffer;
    lookahead = *input;
    int result = expression();
    if (lookahead != '\n' && lookahead != '\0') {
        error();
    }
    printf("Result: %d\n", result);
    return 0;
}

