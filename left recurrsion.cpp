#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_RULES 10
#define MAX_RULE_LEN 20

char rules[MAX_RULES][MAX_RULE_LEN];
char new_rules[MAX_RULES][MAX_RULE_LEN];
int num_rules = 0;

void eliminateLeftRecursion() {
    int i, j, k;
    int has_recursion;

    for (i = 0; i < num_rules; i++) {
        char current_non_terminal = rules[i][0];
        int num_new_rules = 0;
        has_recursion = 0;

        // Extract and eliminate left recursion if present
        for (j = 0; j < i; j++) {
            if (rules[j][0] == current_non_terminal) {
                has_recursion = 1;

                // Extracting non-recursion part of the rule
                for (k = 2; rules[j][k] != '\0'; k++) {
                    new_rules[num_new_rules][k - 2] = rules[j][k];
                }
                // Adding current non-terminal to the non-recursion part
                new_rules[num_new_rules][k - 2] = current_non_terminal;
                // Adding a new non-terminal for recursion
                new_rules[num_new_rules][k - 1] = '\'';
                // Terminating the new rule
                new_rules[num_new_rules][k] = '\0';
                num_new_rules++;
            }
        }

        // If no recursion for the current non-terminal
        if (!has_recursion) {
            strcpy(new_rules[num_new_rules], rules[i]);
            num_new_rules++;
        }

        // Adding new rules after removing left recursion
        for (j = 0; j < num_rules; j++) {
            if (rules[j][0] != current_non_terminal) {
                for (k = 0; rules[j][k] != '\0'; k++) {
                    new_rules[num_new_rules][k] = rules[j][k];
                }
                new_rules[num_new_rules][k] = '\0';
                num_new_rules++;
            }
        }

        // Copying new rules back to original rules array
        for (j = 0; j < num_rules; j++) {
            strcpy(rules[j], new_rules[j]);
        }

        num_rules = num_new_rules;
    }
}

int main() {
    printf("Enter the number of rules: ");
    scanf("%d", &num_rules);

    printf("Enter the rules:\n");
    for (int i = 0; i < num_rules; i++) {
        scanf("%s", rules[i]);
    }

    eliminateLeftRecursion();

    printf("Grammar after eliminating left recursion:\n");
    for (int i = 0; i < num_rules; i++) {
        printf("%s\n", rules[i]);
    }

    return 0;
}

