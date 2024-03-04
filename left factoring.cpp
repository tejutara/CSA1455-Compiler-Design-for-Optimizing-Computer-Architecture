#include <stdio.h>
#include <string.h>

#define MAX_RULES 10
#define MAX_RULE_LEN 20

char rules[MAX_RULES][MAX_RULE_LEN];
char new_rules[MAX_RULES][MAX_RULE_LEN];
int num_rules = 0;

void eliminateLeftFactoring() {
    int i, j, k;
    int has_factoring;

    for (i = 0; i < num_rules; i++) {
        int prefix_len = 0;
        has_factoring = 0;

        // Finding the common prefix length for each pair of rules
        for (j = 0; j < num_rules; j++) {
            if (i != j) {
                int len = 0;
                while (rules[i][len] != '\0' && rules[j][len] != '\0' && rules[i][len] == rules[j][len]) {
                    len++;
                }
                if (len > prefix_len) {
                    prefix_len = len;
                    has_factoring = 1;
                }
            }
        }

        // If factoring exists for the current rule
        if (has_factoring) {
            // Copy the common prefix to the new rule
            for (k = 0; k < prefix_len; k++) {
                new_rules[i][k] = rules[i][k];
            }
            // Add a new non-terminal for the factored out part
            new_rules[i][prefix_len] = '\'';
            // Update the original rule with the factored part
            int factored_pos = prefix_len + 1;
            for (k = 0; rules[i][factored_pos] != '\0'; k++) {
                new_rules[i + 1][k] = rules[i][factored_pos];
                factored_pos++;
            }
            new_rules[i][factored_pos] = '\0';
            // Update the next rule to point to the new non-terminal
            strcpy(new_rules[i + 1], new_rules[i]);
            new_rules[i + 1][prefix_len - 1] = '\'';
            num_rules++;
            i++; // Skip the next rule since it's already added
        } else {
            // If no factoring, just copy the rule as is
            strcpy(new_rules[i], rules[i]);
        }
    }
}

int main() {
    printf("Enter the number of rules: ");
    scanf("%d", &num_rules);

    printf("Enter the rules:\n");
    for (int i = 0; i < num_rules; i++) {
        scanf("%s", rules[i]);
    }

    eliminateLeftFactoring();

    printf("Grammar after eliminating left factoring:\n");
    for (int i = 0; i < num_rules; i++) {
        printf("%s\n", new_rules[i]);
    }

    return 0;
}

