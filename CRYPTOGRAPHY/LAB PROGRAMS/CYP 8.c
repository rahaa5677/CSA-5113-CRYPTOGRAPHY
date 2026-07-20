#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char text[100], key[27], cipher[27] = "";
    int used[26] = {0}, i, j = 0;

    printf("Enter keyword (UPPERCASE): ");
    scanf("%s", key);

    // Create cipher alphabet from keyword
    for (i = 0; key[i] != '\0'; i++) {
        if (!used[key[i] - 'A']) {
            cipher[j++] = key[i];
            used[key[i] - 'A'] = 1;
        }
    }

    // Add remaining letters
    for (i = 0; i < 26; i++) {
        if (!used[i])
            cipher[j++] = 'A' + i;
    }
    cipher[j] = '\0';

    printf("Cipher Alphabet: %s\n", cipher);

    printf("Enter Plaintext (UPPERCASE): ");
    scanf("%s", text);

    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] = cipher[text[i] - 'A'];
    }

    printf("Ciphertext: %s\n", text);

    return 0;
}
