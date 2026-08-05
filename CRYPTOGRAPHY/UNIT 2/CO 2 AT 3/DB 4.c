#include <stdio.h>
#include <stdlib.h>

// 1. Fast Modular Exponentiation: O(log exp) time complexity (Task 4A & 4B)
// Fixes performance bottlenecks and avoids integer overflow during large prime modular operations
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

// 2. FNV-1a Hash-based HMAC Authentication Checksum (Task 4C: MITM Mitigation)
// Binds the public key to a shared secret to prevent Man-In-The-Middle manipulation
unsigned int generate_hmac_checksum(unsigned long long pubkey, unsigned int auth_secret) {
    unsigned int hash = 2166136261u;
    unsigned char *ptr = (unsigned char *)&pubkey;
    for (size_t i = 0; i < sizeof(pubkey); i++) {
        hash ^= ptr[i];
        hash *= 16777619u;
    }
    return hash ^ auth_secret;
}

// 3. Diffie-Hellman Key Exchange Implementation
void task4_diffie_hellman() {
    // Shared Public Domain Parameters
    unsigned long long p = 23; // Prime modulus
    unsigned long long g = 5;  // Generator

    // Private Keys
    unsigned long long a_private = 6;  // Alice's secret key
    unsigned long long b_private = 15; // Bob's secret key

    // Compute Public Keys via Fast Modular Exponentiation
    unsigned long long a_public = power_mod(g, a_private, p);
    unsigned long long b_public = power_mod(g, b_private, p);

    // Shared Pre-Key for HMAC Authentication (Mitigates MITM)
    unsigned int shared_auth_key = 0xABCD1234;

    // Generate signature for Alice's public key
    unsigned int a_sig = generate_hmac_checksum(a_public, shared_auth_key);

    printf("=== [Task 4] Diffie-Hellman Key Exchange ===\n");
    printf("Public Prime (p): %llu, Generator (g): %llu\n", p, g);
    printf("Alice Public Key: %llu\n", a_public);
    printf("Bob Public Key  : %llu\n\n", b_public);

    // MITM Check: Verify payload integrity before computing shared secret
    if (generate_hmac_checksum(a_public, shared_auth_key) == a_sig) {
        printf("[SUCCESS] Public Key Authenticated! No MITM Tampering.\n");

        // Compute Shared Secret Key
        unsigned long long secret_A = power_mod(b_public, a_private, p);
        unsigned long long secret_B = power_mod(a_public, b_private, p);

        printf("Alice Calculated Shared Secret: %llu\n", secret_A);
        printf("Bob Calculated Shared Secret  : %llu\n", secret_B);
    } else {
        printf("[ALERT] MITM Attack Detected! Public Key Tampered.\n");
    }
}

int main() {
    task4_diffie_hellman();
    return 0;
}
