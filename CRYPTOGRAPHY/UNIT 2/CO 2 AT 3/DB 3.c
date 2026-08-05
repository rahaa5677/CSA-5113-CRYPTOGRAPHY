#include <stdio.h>
#include <stdlib.h>

// 1. Fast Modular Exponentiation: O(log e) time complexity
// Replaces naive repetitive multiplication which causes integer overflow and high latency
unsigned long long power_mod(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long res = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

// Extended Euclidean Algorithm for Modular Inverse
unsigned long long mod_inverse(unsigned long long a, unsigned long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

    if (m == 1) return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) x1 += m0;

    return x1;
}

// 2. RSA Operations with CRT Optimization (Task 3A & 3B)
void run_rsa_demo() {
    // Large prime factors p and q
    unsigned long long p = 61;
    unsigned long long q = 53;
    unsigned long long n = p * q; // Modulus n = 3233
    unsigned long long phi = (p - 1) * (q - 1); // 3120

    unsigned long long e = 17; // Public Exponent (gcd(e, phi) == 1)
    unsigned long long d = mod_inverse(e, phi); // Private Exponent (2753)

    unsigned long long message = 65; // Message payload (must be < n)

    printf("=== [Task 3] Debugged RSA Cryptosystem ===\n");
    printf("Public Key  (e, n): (%llu, %llu)\n", e, n);
    printf("Private Key (d, n): (%llu, %llu)\n", d, n);
    printf("Original Message  : %llu\n\n", message);

    // Encryption: c = (m^e) mod n
    unsigned long long ciphertext = power_mod(message, e, n);
    printf("Encrypted Ciphertext: %llu\n", ciphertext);

    // Standard Decryption: m = (c^d) mod n
    unsigned long long standard_decrypted = power_mod(ciphertext, d, n);
    printf("Standard Decrypted  : %llu\n", standard_decrypted);

    // Optimized Decryption using Chinese Remainder Theorem (CRT)
    // CRT reduces computations from mod n (3233) down to mod p (61) and mod q (53)
    unsigned long long dp = d % (p - 1);
    unsigned long long dq = d % (q - 1);
    unsigned long long qinv = mod_inverse(q, p);

    unsigned long long m1 = power_mod(ciphertext, dp, p);
    unsigned long long m2 = power_mod(ciphertext, dq, q);

    unsigned long long h = (qinv * (m1 + p - (m2 % p))) % p;
    unsigned long long crt_decrypted = m2 + h * q;

    printf("CRT Optimized Decrypted: %llu\n\n", crt_decrypted);
}

// 3. Main Function (Fixes undefined reference to 'WinMain')
int main() {
    run_rsa_demo();
    return 0;
}
