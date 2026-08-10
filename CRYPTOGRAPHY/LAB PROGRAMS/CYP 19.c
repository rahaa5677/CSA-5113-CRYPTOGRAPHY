#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Simulated 64-bit block DES encryption function
uint64_t des_encrypt_block(uint64_t block, uint64_t key) {
    return block ^ key; // Simplified mock block cipher execution
}

// Simulated 64-bit block 3DES encryption (Encrypt-Decrypt-Encrypt)
uint64_t triple_des_encrypt_block(uint64_t block, uint64_t k1, uint64_t k2, uint64_t k3) {
    uint64_t stage1 = des_encrypt_block(block, k1);
    uint64_t stage2 = des_encrypt_block(stage1, k2); // XOR inverse is identical here for demo
    uint64_t stage3 = des_encrypt_block(stage2, k3);
    return stage3;
}

int main() {
    uint64_t IV = 0x123456789ABCDEF0ULL;
    uint64_t K1 = 0x0F1571C947D9E859ULL;
    uint64_t K2 = 0x1F2581D957E9F869ULL;
    uint64_t K3 = 0x2F3591E967FAF879ULL;

    uint64_t plaintext[2] = {0x4142434445464748ULL, 0x494A4B4C4D4E4F50ULL}; // 2 blocks
    uint64_t ciphertext[2];

    uint64_t previous_block = IV;

    printf("=== 3DES-CBC Encryption ===\n");
    for (int i = 0; i < 2; i++) {
        // CBC Rule: Ciphertext[i] = Encrypt(Plaintext[i] ^ Ciphertext[i-1])
        uint64_t xor_input = plaintext[i] ^ previous_block;
        ciphertext[i] = triple_des_encrypt_block(xor_input, K1, K2, K3);
        previous_block = ciphertext[i];

        printf("Block %d Ciphertext: 0x%016LLX\n", i + 1, (unsigned long long)ciphertext[i]);
    }

    return 0;
}
