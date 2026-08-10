#include <stdio.h>
#include <string.h>

void encryptOneTimePad(const char *plaintext, const int *key, char *ciphertext, int len) {
    for (int i = 0; i < len; i++) {
        int p_val = plaintext[i] - 'a';
        int c_val = (p_val + key[i]) % 26;
        ciphertext[i] = (char)(c_val + 'a');
    }
    ciphertext[len] = '\0';
}

void findKeyForTarget(const char *ciphertext, const char *targetPlaintext, int *newKey, int len) {
    for (int i = 0; i < len; i++) {
        int c_val = ciphertext[i] - 'a';
        int target_val = targetPlaintext[i] - 'a';
        newKey[i] = (c_val - target_val + 26) % 26;
    }
}

int main() {
    printf("=== QUESTION 14: ONE-TIME PAD / VIGENÈRE CIPHER ===\n\n");

    // --- Part (a) ---
    char plaintext1[] = "sendmoremoney";
    int key1[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int len = strlen(plaintext1);
    char ciphertext[30];

    encryptOneTimePad(plaintext1, key1, ciphertext, len);

    printf("--- Part (a) ---\n");
    printf("Plaintext:  %s\n", plaintext1);
    printf("Key Stream: ");
    for (int i = 0; i < len; i++) printf("%d ", key1[i]);
    printf("\nCiphertext: %s\n\n", ciphertext);

    // --- Part (b) ---
    char targetPlaintext[] = "cashnotneeded";
    int key2[30];

    findKeyForTarget(ciphertext, targetPlaintext, key2, len);

    printf("--- Part (b) ---\n");
    printf("Ciphertext:       %s\n", ciphertext);
    printf("Target Plaintext: %s\n", targetPlaintext);
    printf("Required Key Stream: ");
    for (int i = 0; i < len; i++) {
        printf("%d ", key2[i]);
    }
    printf("\n");

    return 0;
}
