#include <stdio.h>
#include <stdint.h>

// Mock block cipher encryption (XOR with key for demonstration)
uint8_t encrypt_block(uint8_t block, uint8_t key) {
    return block ^ key ^ 0xAA; // Simple deterministic function
}

uint8_t cbc_mac(uint8_t *msg, int blocks, uint8_t key) {
    uint8_t mac = 0;
    for (int i = 0; i < blocks; i++) {
        mac = encrypt_block(msg[i] ^ mac, key);
    }
    return mac;
}

int main() {
    uint8_t key = 0x47;
    uint8_t X = 0x3F;

    // 1. Calculate MAC for one-block message X
    uint8_t T = cbc_mac(&X, 1, key);
    printf("One-block message X: 0x%02X -> MAC (T): 0x%02X\n", X, T);

    // 2. Forged two-block message X || (X ^ T)
    uint8_t forged_msg[2] = {X, X ^ T};
    uint8_t forged_mac = cbc_mac(forged_msg, 2, key);

    printf("Forged two-block message: [0x%02X, 0x%02X]\n", forged_msg[0], forged_msg[1]);
    printf("Calculated CBC MAC for forged message: 0x%02X\n", forged_mac);

    if (forged_mac == T) {
        printf("Forgery Successful! MAC matches T without key knowledge.\n");
    }

    return 0;
}
