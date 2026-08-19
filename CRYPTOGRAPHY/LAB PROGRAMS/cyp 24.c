#include <stdio.h>

// Extended Euclidean Algorithm to find inverse
long long extended_gcd(long long a, long long b, long long *x, long long *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    long long x1, y1;
    long long gcd = extended_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

// Function to find modular inverse
long long mod_inverse(long long e, long long phi) {
    long long x, y;
    long long g = extended_gcd(e, phi, &x, &y);
    if (g != 1) return -1; // Inverse doesn't exist
    return (x % phi + phi) % phi;
}

int main() {
    long long n = 3599;
    long long e = 31;
    long long p = 0, q = 0;

    // Trial and error factorization
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            p = i;
            q = n / i;
            break;
        }
    }

    if (p == 0) {
        printf("Failed to factorize n.\n");
        return 1;
    }

    long long phi = (p - 1) * (q - 1);
    long long d = mod_inverse(e, phi);

    printf("Factors found: p = %lld, q = %lld\n", p, q);
    printf("Euler's Totient phi(n) = %lld\n", phi);
    printf("Private Key d = %lld\n", d);

    return 0;
}
