#include <stdio.h>
#include <math.h>

int main() {
    // Calculating 25! and 24! using logarithmic sums
    double log2_25fact = 0;
    for (int i = 1; i <= 25; i++) {
        log2_25fact += log2(i);
    }

    double log2_24fact = 0;
    for (int i = 1; i <= 24; i++) {
        log2_24fact += log2(i);
    }

    printf("11. Total possible Playfair matrices (25!):\n");
    printf("    Approximate power of 2: 2^(%.2f)\n", log2_25fact);

    printf("\n11a. Effectively unique Playfair keys (24!):\n");
    printf("    Approximate power of 2: 2^(%.2f)\n", log2_24fact);

    return 0;
}
