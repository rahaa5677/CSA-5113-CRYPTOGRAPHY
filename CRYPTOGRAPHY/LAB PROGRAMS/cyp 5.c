#include <stdio.h>
#include <string.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    char text[100];
    int a, b, i;

    printf("Enter plaintext (UPPERCASE): ");
    scanf("%s", text);

    printf("Enter key a: ");
    scanf("%d", &a);

    printf("Enter key b: ");
    scanf("%d", &b);

    if (gcd(a, 26) != 1) {
        printf("Invalid key! 'a' must be coprime with 26.");
        return 0;
    }

    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = ((a * (text[i] - 'A') + b) % 26) + 'A';
        }
    }

    printf("Ciphertext: %s", text);

    return 0;
}
