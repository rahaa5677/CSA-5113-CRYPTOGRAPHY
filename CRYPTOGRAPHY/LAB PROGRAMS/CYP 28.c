#include <stdio.h>

// Extended Euclidean Algorithm for mod inverse
long long mod_inverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;
    if (m == 1) return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m; a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

int main() {
    long long q = 10007; // Prime modulus
    long long a = 7;     // Public multiplier

    // Secrets
    long long x_alice = 123;
    long long x_bob = 456;

    // Transmitted values (Insecure modified protocol)
    long long A = (x_alice * a) % q;
    long long B = (x_bob * a) % q;

    // Shared key calculation
    long long key_alice = (x_alice * B) % q;
    long long key_bob = (x_bob * A) % q;

    printf("Alice Key: %lld, Bob Key: %lld\n", key_alice, key_bob);

    // Eavesdropper (Eve) attack:
    long long a_inv = mod_inverse(a, q);
    long long eve_x_alice = (A * a_inv) % q;
    long long eve_x_bob = (B * a_inv) % q;
    long long eve_key = (eve_x_alice * eve_x_bob * a) % q;

    printf("\n--- EVE ATTACK ---");
    printf("\nEve recovered Alice's secret x_A: %lld", eve_x_alice);
    printf("\nEve recovered Bob's secret x_B: %lld", eve_x_bob);
    printf("\nEve recovered Shared Key: %lld\n", eve_key);

    return 0;
}
