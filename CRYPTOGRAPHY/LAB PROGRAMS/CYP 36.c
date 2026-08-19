#include <stdio.h>
#include <ctype.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

void affine_encrypt(const char *plaintext, char *ciphertext, int a, int b) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = ((a * (plaintext[i] - base) + b) % 26) + base;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
}

int main() {
    int a = 2, b = 3;
    printf("Testing invalid key (a = %d, b = %d):\n", a, b);
    if (gcd(a, 26) != 1) {
        printf("Error: 'a' and 26 are not coprime (gcd = %d). Encryption is NOT one-to-one!\n", gcd(a, 26));
        printf("Demonstration: E([2,3], 0) = %d, E([2,3], 13) = %d\n\n", (a*0 + b)%26, (a*13 + b)%26);
    }

    a = 5; // Valid key
    if (gcd(a, 26) == 1) {
        char pt[] = "HELLO";
        char ct[10];
        affine_encrypt(pt, ct, a, b);
        printf("Testing valid key (a = %d, b = %d):\n", a, b);
        printf("Plaintext: %s -> Ciphertext: %s\n", pt, ct);
    }

    return 0;
}
