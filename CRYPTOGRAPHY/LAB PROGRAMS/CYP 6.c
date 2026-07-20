#include <stdio.h>

int main() {
    int P1 = 4, C1 = 1;   // E -> B
    int P2 = 19, C2 = 20; // T -> U

    int a, b;

    for (a = 1; a < 26; a++) {
        for (b = 0; b < 26; b++) {
            if (((a * P1 + b) % 26 == C1) &&
                ((a * P2 + b) % 26 == C2)) {
                printf("Key Found:\n");
                printf("a = %d\n", a);
                printf("b = %d\n", b);
            }
        }
    }

    return 0;
}
