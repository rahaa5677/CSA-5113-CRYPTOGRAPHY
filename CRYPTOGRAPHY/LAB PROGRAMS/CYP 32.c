#include <stdio.h>
#include <stdlib.h>

// Simulating RSA signature: S = M^d mod n (Deterministic)
long rsa_sign(long m, long d, long n) {
    long s = 1;
    for (int i = 0; i < d; i++) s = (s * m) % n;
    return s;
}

// Simulating DSA signature component: r = (g^k mod p) mod q (Probabilistic)
void dsa_sign(long m, long x, long p, long q, long g, long *r, long *s) {
    long k = rand() % (q - 1) + 1; // Random per signature
    *r = (k * g) % q;             // Simplified simulation
    *s = (m + x * (*r)) % q;
}

int main() {
    long message = 42;
    long rsa_d = 7, rsa_n = 33;
    long dsa_x = 5, dsa_p = 23, dsa_q = 11, dsa_g = 4;

    printf("--- RSA Signatures for Same Message ---\n");
    printf("Sig 1: %ld\n", rsa_sign(message, rsa_d, rsa_n));
    printf("Sig 2: %ld\n", rsa_sign(message, rsa_d, rsa_n));

    printf("\n--- DSA Signatures for Same Message ---\n");
    long r1, s1, r2, s2;
    dsa_sign(message, dsa_x, dsa_p, dsa_q, dsa_g, &r1, &s1);
    dsa_sign(message, dsa_x, dsa_p, dsa_q, dsa_g, &r2, &s2);
    printf("Sig 1: (r=%ld, s=%ld)\n", r1, s1);
    printf("Sig 2: (r=%ld, s=%ld)\n", r2, s2);

    return 0;
}
