#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8

// Function to apply 1-bit followed by zeros padding (Bit-padding / PKCS-style concept)
int addPadding(const char *input, unsigned char *paddedOutput, int inLen) {
    int padNeeded = BLOCK_SIZE - (inLen % BLOCK_SIZE);

    // Copy original data
    memcpy(paddedOutput, input, inLen);

    // If message is already a multiple of block size, append a full padding block
    // Motivation: Unambiguous removal by receiver.
    if (padNeeded == 0) {
        padNeeded = BLOCK_SIZE;
    }

    // Append 1 bit (0x80 = 10000000 in binary) followed by 0 bits (0x00)
    paddedOutput[inLen] = 0x80;
    for (int i = 1; i < padNeeded; i++) {
        paddedOutput[inLen + i] = 0x00;
    }

    return inLen + padNeeded;
}

int main() {
    char message1[] = "HELLO";       // 5 bytes (incomplete block)
    char message2[] = "12345678";    // 8 bytes (exact block size)

    unsigned char padded1[32], padded2[32];

    int len1 = addPadding(message1, padded1, strlen(message1));
    int len2 = addPadding(message2, padded2, strlen(message2));

    printf("=== Question 21: Padding Demonstration ===\n\n");

    printf("1. Incomplete Block Message (\"HELLO\", 5 bytes):\n");
    printf("   Padded Length: %d bytes\n   Hex Output:    ", len1);
    for (int i = 0; i < len1; i++) printf("%02X ", padded1[i]);
    printf("\n\n");

    printf("2. Exact Block Message (\"12345678\", 8 bytes):\n");
    printf("   Padded Length: %d bytes (Full extra padding block added)\n   Hex Output:    ", len2);
    for (int i = 0; i < len2; i++) printf("%02X ", padded2[i]);
    printf("\n");

    return 0;
}
