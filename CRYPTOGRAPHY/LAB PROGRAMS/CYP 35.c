#include <stdio.h>
#include <ctype.h>
#include <string.h>

void vigenere_otp_encrypt(const char *plaintext, const int *key, char *ciphertext, int len) {
    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = ((plaintext[i] - base + key[i]) % 26) + base;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[len] = '\0';
}

int main() {
    char plaintext[] = "HELLO";
    int key[] = {3, 19, 5, 12, 1}; // Key stream between 0 and 25
    int len = strlen(plaintext);
    char ciphertext[10];

    vigenere_otp_encrypt(plaintext, key, ciphertext, len);

    printf("Plaintext:  %s\n", plaintext);
    printf("Key Stream: ");
    for (int i = 0; i < len; i++) printf("%d ", key[i]);
    printf("\nCiphertext: %s\n", ciphertext);

    return 0;
}
