#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    int K[2][2] = {{9, 4}, {5, 7}};
    int K_inv[2][2] = {{5, 12}, {15, 25}}; // Derived inverse key

    char text[] = "meet me at the usual place at ten rather than eight oclock";
    char clean[200] = "";
    int len = 0;

    // Process plaintext into uppercase alphabet-only string
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            clean[len++] = toupper(text[i]);
        }
    }
    // Pad with 'X' if odd
    if (len % 2 != 0) {
        clean[len++] = 'X';
    }
    clean[len] = '\0';

    char ciphertext[200] = "";
    char decrypted[200] = "";

    // Encryption: C = K * P mod 26
    for (int i = 0; i < len; i += 2) {
        int p1 = clean[i] - 'A';
        int p2 = clean[i + 1] - 'A';

        ciphertext[i] = ((K[0][0] * p1 + K[0][1] * p2) % 26) + 'A';
        ciphertext[i + 1] = ((K[1][0] * p1 + K[1][1] * p2) % 26) + 'A';
    }
    ciphertext[len] = '\0';

    // Decryption: P = K_inv * C mod 26
    for (int i = 0; i < len; i += 2) {
        int c1 = ciphertext[i] - 'A';
        int c2 = ciphertext[i + 1] - 'A';

        decrypted[i] = ((K_inv[0][0] * c1 + K_inv[0][1] * c2) % 26) + 'A';
        decrypted[i + 1] = ((K_inv[1][0] * c1 + K_inv[1][1] * c2) % 26) + 'A';
    }
    decrypted[len] = '\0';

    printf("Plaintext:  %s\n", clean);
    printf("Encrypted:  %s\n", ciphertext);
    printf("Decrypted:  %s\n", decrypted);

    return 0;
}
