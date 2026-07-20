#include <stdio.h>
#include <string.h>

int main() {
    char text[100];
    char key[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    int i;

    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);

    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] = key[text[i] - 'A'];
        else if (text[i] >= 'a' && text[i] <= 'z')
            text[i] = key[text[i] - 'a'] + 32;
    }

    printf("Ciphertext: %s", text);

    return 0;
}
