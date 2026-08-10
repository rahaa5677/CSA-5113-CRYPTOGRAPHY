#include <stdio.h>
#include <stdint.h>

// Helper functions for bit permutations
uint8_t permute(uint8_t input, const int table[], int size) {
    uint8_t output = 0;
    for (int i = 0; i < size; i++) {
        if ((input >> (8 - table[i])) & 1)
            output |= (1 << (size - 1 - i));
    }
    return output;
}

uint16_t permute10(uint16_t input, const int table[], int size) {
    uint16_t output = 0;
    for (int i = 0; i < size; i++) {
        if ((input >> (10 - table[i])) & 1)
            output |= (1 << (size - 1 - i));
    }
    return output;
}

// Generate S-DES subkeys K1 and K2
void generate_sdes_keys(uint16_t key10, uint8_t *k1, uint8_t *k2) {
    int P10[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
    int P8[]  = {6, 3, 7, 4, 8, 5, 10, 9};

    uint16_t p10 = permute10(key10, P10, 10);
    uint8_t l = (p10 >> 5) & 0x1F;
    uint8_t r = p10 & 0x1F;

    // Shift 1
    l = ((l << 1) | (l >> 4)) & 0x1F;
    r = ((r << 1) | (r >> 4)) & 0x1F;
    *k1 = (uint8_t)permute10((l << 5) | r, P8, 8);

    // Shift 2
    l = ((l << 2) | (l >> 3)) & 0x1F;
    r = ((r << 2) | (r >> 3)) & 0x1F;
    *k2 = (uint8_t)permute10((l << 5) | r, P8, 8);
}

// Feistel function
uint8_t fk(uint8_t in, uint8_t key) {
    int EP[] = {4, 1, 2, 3, 2, 3, 4, 1};
    int P4[] = {2, 4, 3, 1};
    int S0[4][4] = {{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}};
    int S1[4][4] = {{0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3}};

    uint8_t l = (in >> 4) & 0x0F;
    uint8_t r = in & 0x0F;

    uint8_t ep = permute(r, EP, 8) ^ key;
    uint8_t ep_l = (ep >> 4) & 0x0F;
    uint8_t ep_r = ep & 0x0F;

    int r0 = ((ep_l & 8) >> 2) | (ep_l & 1);
    int c0 = (ep_l >> 1) & 3;
    int r1 = ((ep_r & 8) >> 2) | (ep_r & 1);
    int c1 = (ep_r >> 1) & 3;

    uint8_t s_out = (S0[r0][c0] << 2) | S1[r1][c1];
    return (l ^ permute(s_out, P4, 4)) << 4 | r;
}

// Full S-DES Encryption
uint8_t sdes_encrypt(uint8_t block, uint8_t k1, uint8_t k2) {
    int IP[] = {2, 6, 3, 1, 4, 8, 5, 7};
    int IP_INV[] = {4, 1, 3, 5, 7, 2, 8, 6};

    uint8_t val = permute(block, IP, 8);
    val = fk(val, k1);
    val = (val >> 4) | (val << 4);
    val = fk(val, k2);
    return permute(val, IP_INV, 8);
}

void print_binary8(uint8_t val) {
    for (int i = 7; i >= 0; i--) printf("%d", (val >> i) & 1);
}

int main() {
    uint16_t key = 0b0111111101;
    uint8_t counter = 0b00000000;
    uint8_t plaintext[3] = {0b00000001, 0b00000010, 0b00000100};
    uint8_t ciphertext[3], decrypted[3];

    uint8_t k1, k2;
    generate_sdes_keys(key, &k1, &k2);

    printf("=== Question 23: S-DES Counter (CTR) Mode ===\n\n");

    // CTR Encryption: C_i = P_i ^ Encrypt(Counter_i)
    uint8_t current_ctr = counter;
    for (int i = 0; i < 3; i++) {
        uint8_t encrypted_ctr = sdes_encrypt(current_ctr, k1, k2);
        ciphertext[i] = plaintext[i] ^ encrypted_ctr;
        current_ctr++; // Increment counter
    }

    // CTR Decryption: P_i = C_i ^ Encrypt(Counter_i)
    current_ctr = counter;
    for (int i = 0; i < 3; i++) {
        uint8_t encrypted_ctr = sdes_encrypt(current_ctr, k1, k2);
        decrypted[i] = ciphertext[i] ^ encrypted_ctr;
        current_ctr++; // Increment counter
    }

    for (int i = 0; i < 3; i++) {
        printf("Block %d:\n", i + 1);
        printf("  Ciphertext: "); print_binary8(ciphertext[i]); printf("\n");
        printf("  Decrypted:  "); print_binary8(decrypted[i]); printf("\n");
    }

    return 0;
}
