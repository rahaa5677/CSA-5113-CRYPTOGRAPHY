#include <stdio.h>

// Modular exponentiation: (base^exp) % mod
long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return res;
}

int main() {
    long long n = 3599; // Public modulus
    long long e = 31;   // Public exponent

    // 1. Eve builds a lookup table (Codebook Attack) for all 26 possible values
    long long codebook[26];
    printf("--- Eve's Precomputed Codebook ---\n");
    for (int i = 0; i < 26; i++) {
        codebook[i] = power(i, e, n);
    }
    printf("Codebook built for characters A-Z (0-25).\n\n");

    // 2. Alice encrypts message "CAB" -> [2, 0, 1]
    int plaintext[] = {2, 0, 1};
    int length = 3;
    long long ciphertext[3];

    for (int i = 0; i < length; i++) {
        ciphertext[i] = power(plaintext[i], e, n);
    }

    // 3. Eve intercepts ciphertext and decrypts using lookup table
    printf("Intercepted Ciphertext: ");
    for (int i = 0; i < length; i++) printf("%lld ", ciphertext[i]);
    printf("\nDecrypted Message by Eve: ");

    for (int i = 0; i < length; i++) {
        for (int c = 0; c < 26; c++) {
            if (ciphertext[i] == codebook[c]) {
                printf("%c", (char)('A' + c));
                break;
            }
        }
    }
    printf("\n");

    return 0;
}
