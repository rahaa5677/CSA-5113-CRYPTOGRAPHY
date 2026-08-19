#include <stdio.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    long long n = 3599; // Public modulus n = p * q
    long long e = 31;   // Public exponent

    // Suppose a known plaintext block m shares a factor with n
    // e.g., m is a multiple of p (59 * 2 = 118)
    long long m = 118;

    long long factor = gcd(m, n);

    if (factor > 1 && factor < n) {
        printf("Common factor found!\n");
        long long p = factor;
        long long q = n / p;
        long long phi = (p - 1) * (q - 1);

        printf("Recovered p = %lld, q = %lld\n", p, q);
        printf("RSA compromised! Attacker can now calculate the private key.\n");
    } else {
        printf("No useful common factor found.\n");
    }

    return 0;
}
