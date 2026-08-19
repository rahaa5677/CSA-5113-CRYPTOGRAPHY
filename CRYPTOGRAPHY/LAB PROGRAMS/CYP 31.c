#include <stdio.h>
#include <stdint.h>

// Subkey generation for 64-bit block size (Rb = 0x1B)
void generate_subkeys_64(uint64_t L, uint64_t *K1, uint64_t *K2) {
    uint64_t Rb = 0x1B;

    // Key 1 derivation
    if ((L & 0x8000000000000000ULL) == 0) {
        *K1 = L << 1;
    } else {
        *K1 = (L << 1) ^ Rb;
    }

    // Key 2 derivation
    if ((*K1 & 0x8000000000000000ULL) == 0) {
        *K2 = *K1 << 1;
    } else {
        *K2 = (*K1 << 1) ^ Rb;
    }
}

int main() {
    uint64_t L = 0x2B7E151628AED2A6ULL; // Mock cipher output E(K, 0)
    uint64_t K1, K2;

    generate_subkeys_64(L, &K1, &K2);

    printf("E(K, 0): 0x%016llX\n", L);
    printf("Subkey 1 (K1): 0x%016llX\n", K1);
    printf("Subkey 2 (K2): 0x%016llX\n", K2);

    return 0;
}
