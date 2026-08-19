#include <stdio.h>

// Function demonstrating how leaking (e1, d1) allows factorizing n
int main() {
    long long n = 3599;
    long long e1 = 31, d1 = 3031; // Old keypair (Leaked d1)
    long long e2 = 7;             // New public key with SAME n

    // Attacker calculates k = e1 * d1 - 1, which is a multiple of phi(n)
    long long k = e1 * d1 - 1; // 31 * 3031 - 1 = 93960

    // Since phi(n) divides k, attacker can easily extract phi(n) and factor n
    // For this demonstration, we show how e2 is immediately cracked:
    long long phi = 3480; // Derived by attacker from k

    // Calculate new private key d2
    long long d2 = 0;
    for (long long i = 1; i < phi; i++) {
        if ((e2 * i) % phi == 1) {
            d2 = i;
            break;
        }
    }

    printf("CRITICAL SECURITY RISK DEMO:\n");
    printf("Old Keypair: e1 = %lld, Leaked d1 = %lld\n", e1, d1);
    printf("New Public Key (same n): e2 = %lld\n", e2);
    printf("Attacker derived new Private Key d2 = %lld without knowing p and q initially!\n", d2);

    return 0;
}
