#include <stdio.h>

int mod26(int a) {
    int res = a % 26;
    return res < 0 ? res + 26 : res;
}

int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

int main() {
    // Known pairs: P = [[7, 4], [11, 11]] ("HE", "LL")
    // Corresponding C = [[11, 12], [23, 14]]
    int P[2][2] = {{7, 4}, {11, 11}};
    int C[2][2] = {{11, 12}, {23, 14}};

    // Compute det(P)
    int detP = mod26(P[0][0] * P[1][1] - P[0][1] * P[1][2]);
    int det_inv = mod_inverse(detP, 26);

    if (det_inv == -1) {
        printf("Matrix P is not invertible mod 26. Need different plaintext blocks.\n");
        return 1;
    }

    // P_inv = det_inv * adj(P) mod 26
    int P_inv[2][2];
    P_inv[0][0] = mod26(P[1][1] * det_inv);
    P_inv[0][1] = mod26(-P[0][1] * det_inv);
    P_inv[1][0] = mod26(-P[1][0] * det_inv);
    P_inv[1][1] = mod26(P[0][0] * det_inv);

    // K = P_inv * C mod 26
    int K[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            K[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                K[i][j] += P_inv[i][k] * C[k][j];
            }
            K[i][j] = mod26(K[i][j]);
        }
    }

    printf("Recovered $2 \\times 2$ Key Matrix:\n");
    printf("[%d, %d]\n[%d, %d]\n", K[0][0], K[0][1], K[1][0], K[1][1]);

    return 0;
}
