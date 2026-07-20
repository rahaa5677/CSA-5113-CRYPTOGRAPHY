#include <stdio.h>
#include <string.h>

int main() {
    char text[100], key[100];
    int i, j = 0, len;

    printf("Enter Plaintext (UPPERCASE): ");
    scanf("%s", text);

    printf("Enter Key (UPPERCASE): ");
    scanf("%s", key);

    len = strlen(key);

    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = ((text[i] - 'A') + (key[j % len] - 'A')) % 26 + 'A';
            j++;
        }
    }

    printf("Ciphertext: %s", text);

    return 0;
}
