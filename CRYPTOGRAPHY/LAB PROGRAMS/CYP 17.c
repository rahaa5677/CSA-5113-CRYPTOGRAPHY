#include <stdio.h>
#include <stdint.h>

// Shift schedule for DES encryption (Left shifts)
const int SHIFT_SCHEDULE[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

// Cyclic right shift on a 28-bit integer
uint32_t rightShift28(uint32_t val, int shifts) {
    return ((val >> shifts) | (val << (28 - shifts))) & 0x0FFFFFFF;
}

// Cyclic left shift on a 28-bit integer
uint32_t leftShift28(uint32_t val, int shifts) {
    return ((val << shifts) | (val >> (28 - shifts))) & 0x0FFFFFFF;
}

int main() {
    // Dummy 28-bit halves after PC-1 permuted choice
    uint32_t C = 0x0A2B3C4;
    uint32_t D = 0x056789A;

    printf("=== DES Decryption Subkey Generation ===\n\n");

    // Advance C and D to C16 and D16 by performing standard 16 left shifts
    for (int i = 0; i < 16; i++) {
        C = leftShift28(C, SHIFT_SCHEDULE[i]);
        D = leftShift28(D, SHIFT_SCHEDULE[i]);
    }

    printf("Starting at Round 16 halves:\n");
    printf("C16 = 0x%07X, D16 = 0x%07X\n\n", C, D);

    // Generate decryption keys directly using right-shifts
    for (int round = 16; round >= 1; round--) {
        // PC-2 permutation would be applied here to (C, D) to get K_round
        printf("Decryption Round %2d uses halves: C = 0x%07X, D = 0x%07X\n", round, C, D);

        // Apply right shifts to step down to the previous subkey half
        int shift_amount = SHIFT_SCHEDULE[round - 1];
        C = rightShift28(C, shift_amount);
        D = rightShift28(D, shift_amount);
    }

    return 0;
}
