#include <stdio.h>
#include <string.h>

int main() {
    char text[100];
    int k, i;

    printf("Enter a message: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter the key (1-25): ");
    scanf("%d", &k);

    if (k < 1 || k > 25) {
        printf("Invalid key! Key must be between 1 and 25.\n");
        return 0;
    }

    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = ((text[i] - 'A' + k) % 26) + 'A';
        }
        else if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = ((text[i] - 'a' + k) % 26) + 'a';
        }
    }

    printf("Encrypted message: %s\n", text);

    return 0;
}
