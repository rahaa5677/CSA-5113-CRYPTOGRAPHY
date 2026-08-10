#include <stdio.h>

// Standard PC-2 Table (1-indexed)
const int PC2[48] = {
    14, 17, 11, 24,  1,  5,    3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,   16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,   30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,   46, 42, 50, 36, 29, 32
};

int main() {
    int left_valid = 1, right_valid = 1;

    // Check first 24 output bits (Indices 1 to 28 correspond to C_i)
    for (int i = 0; i < 24; i++) {
        if (PC2[i] < 1 || PC2[i] > 28) {
            left_valid = 0;
        }
    }

    // Check second 24 output bits (Indices 29 to 56 correspond to D_i)
    for (int i = 24; i < 48; i++) {
        if (PC2[i] < 29 || PC2[i] > 56) {
            right_valid = 0;
        }
    }

    printf("=== DES PC-2 Property Verification ===\n");
    printf("1. First 24 bits of subkey come solely from C_i (bits 1-28):  %s\n", left_valid ? "VERIFIED" : "FAILED");
    printf("2. Second 24 bits of subkey come solely from D_i (bits 29-56): %s\n", right_valid ? "VERIFIED" : "FAILED");

    return 0;
}
