#include <stdio.h>

int modInverse(int a, int m) {
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

int main() {
    // Example known plaintext-ciphertext block pair (2x2)
    // Plaintext: "HILL" -> P1 = "HI" (7, 8), P2 = "LL" (11, 11)
    // Matrix P: [[7, 8], [11, 11]]
    int P[2][2] = {{7, 8}, {11, 11}};

    // Corresponding Ciphertext output matrix C
    int C[2][2] = {{19, 16}, {4, 19}};

    // Compute det(P)
    int detP = (P[0][0] * P[1][1] - P[0][1] * P[1][0]) % 26;
    if (detP < 0) detP += 26;

    int detP_inv = modInverse(detP, 26);
    if (detP_inv == -1) {
        printf("Matrix P is not invertible mod 26. Need different plaintext blocks.\n");
        return 1;
    }

    // Compute P_inv mod 26
    int P_inv[2][2];
    P_inv[0][0] = ( P[1][1] * detP_inv) % 26;
    P_inv[0][1] = (-P[0][1] * detP_inv) % 26;
    P_inv[1][0] = (-P[1][0] * detP_inv) % 26;
    P_inv[1][1] = ( P[0][0] * detP_inv) % 26;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (P_inv[i][j] < 0) P_inv[i][j] += 26;
        }
    }

    // Recover Key: K = P_inv * C mod 26
    int K[2][2] = {0};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                K[i][j] = (K[i][j] + P_inv[i][k] * C[k][j]) % 26;
            }
            if (K[i][j] < 0) K[i][j] += 26;
        }
    }

    printf("Recovered Key Matrix K:\n");
    printf("[%2d  %2d]\n", K[0][0], K[0][1]);
    printf("[%2d  %2d]\n", K[1][0], K[1][1]);

    return 0;
}
