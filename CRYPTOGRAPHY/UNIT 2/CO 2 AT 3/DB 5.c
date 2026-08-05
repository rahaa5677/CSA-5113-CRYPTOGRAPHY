#include <stdio.h>
#include <stdlib.h>

// 1. Modular Inverse Function (Fixes implicit declaration error)
// Uses Extended Euclidean Algorithm to calculate (1 / a) mod m
long long mod_inverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

    if (m == 1) return 0;

    a = (a % m + m) % m; // Ensure positive remainder

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

// Elliptic Curve Point Structure: (x, y) over Finite Field
typedef struct {
    long long x;
    long long y;
    int is_infinity; // Point at infinity flag
} ECPoint;

// Curve Parameters: y^2 = x^3 + ax + b (mod p)
long long curve_a = 2;
long long curve_b = 3;
long long curve_p = 97;

// 2. Point Addition & Doubling Logic (Task 5A)
ECPoint ec_point_add(ECPoint P, ECPoint Q) {
    if (P.is_infinity) return Q;
    if (Q.is_infinity) return P;

    ECPoint R;
    R.is_infinity = 0;
    long long m;

    // Handle vertical line (P + (-P) = Identity Point O)
    if (P.x == Q.x && (P.y != Q.y || P.y == 0)) {
        R.is_infinity = 1;
        return R;
    }

    if (P.x == Q.x && P.y == Q.y) {
        // Point Doubling: Slope m = (3*x1^2 + a) / (2*y1) mod p
        long long num = (3 * P.x * P.x + curve_a) % curve_p;
        long long den = mod_inverse(2 * P.y, curve_p);
        m = (num * den) % curve_p;
    } else {
        // Point Addition: Slope m = (y2 - y1) / (x2 - x1) mod p
        long long num = (Q.y - P.y + curve_p) % curve_p;
        long long den = mod_inverse((Q.x - P.x + curve_p) % curve_p, curve_p);
        m = (num * den) % curve_p;
    }

    R.x = (m * m - P.x - Q.x) % curve_p;
    if (R.x < 0) R.x += curve_p;

    R.y = (m * (P.x - R.x) - P.y) % curve_p;
    if (R.y < 0) R.y += curve_p;

    return R;
}

// 3. Double-and-Add Scalar Multiplication Algorithm: O(log k) Complexity (Task 5B)
ECPoint ec_scalar_multiply(long long k, ECPoint P) {
    ECPoint result = {0, 0, 1}; // Initialize as Point at Infinity
    ECPoint addend = P;

    while (k > 0) {
        if (k & 1) {
            result = ec_point_add(result, addend);
        }
        addend = ec_point_add(addend, addend); // Double
        k >>= 1;
    }
    return result;
}

void task5_ecc_demo() {
    // Base Point G on curve y^2 = x^3 + 2x + 3 (mod 97)
    ECPoint Generator = {3, 6, 0};
    long long private_key = 5;

    // Compute Public Key: Q = d * G
    ECPoint public_key = ec_scalar_multiply(private_key, Generator);

    printf("=== [Task 5] Elliptic Curve Cryptography (ECC) ===\n");
    printf("Curve Parameters : y^2 = x^3 + %lldx + %lld (mod %lld)\n", curve_a, curve_b, curve_p);
    printf("Base Point G     : (%lld, %lld)\n", Generator.x, Generator.y);
    printf("Private Key      : %lld\n", private_key);
    printf("Public Key Point : (%lld, %lld)\n", public_key.x, public_key.y);
}

int main() {
    task5_ecc_demo();
    return 0;
}
