#include <stdio.h>
#include <stdint.h>

// PC-1 table mapping 64-bit input key to 56-bit key
const int PC1[] = {
    57, 49, 41, 33, 25, 17, 9,   1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4
};

uint64_t des_permute_key(uint64_t key64) {
    uint64_t key56 = 0;
    for (int i = 0; i < 56; i++) {
        int bit_pos = PC1[i] - 1;
        uint64_t bit = (key64 >> (63 - bit_pos)) & 1;
        key56 = (key56 << 1) | bit;
    }
    return key56;
}

int main() {
    uint64_t raw_key = 0x133457799BBCDFF1ULL; // 64-bit key with parity
    uint64_t des_key56 = des_permute_key(raw_key);

    printf("Input 64-bit Key: 0x%016llX\n", raw_key);
    printf("Extracted 56-bit Key: 0x%014llX\n", des_key56);

    return 0;
}
