#include <stdio.h>

int main() {
    int a, b, c, d, e, f, x, y, z;

    // Original expressions
    a = b * c + d * e;
    x = b * c;
    y = d * e;
    f = a + y;

    // After common subexpression elimination
    x = b * c;
    y = d * e;
    a = x + y;
    f = a;

    // Print results
    printf("Original expressions:\n");
    printf("a = b * c + d * e\n");
    printf("f = a + d * e\n\n");

    printf("After common subexpression elimination:\n");
    printf("a = b * c + d * e\n");
    printf("f = a\n");

    return 0;
}

