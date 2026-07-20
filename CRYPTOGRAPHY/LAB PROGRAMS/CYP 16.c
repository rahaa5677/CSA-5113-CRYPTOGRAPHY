#include <stdio.h>
#include <string.h>

int main() {
    char cipher[500];
    int freq[26] = {0}, i;

    printf("Enter Cipher Text (UPPERCASE):\n");
    fgets(cipher, sizeof(cipher), stdin);

    // Count letter frequencies
    for(i = 0; cipher[i] != '\0'; i++) {
        if(cipher[i] >= 'A' && cipher[i] <= 'Z')
            freq[cipher[i] - 'A']++;
    }

    printf("\nLetter Frequencies:\n");
    for(i = 0; i < 26; i++)
        printf("%c : %d\n", 'A' + i, freq[i]);

    printf("\nMost common English letters:\n");
    printf("E T A O I N S H R D L U\n");

    printf("\nTry mapping the most frequent cipher letters\n");
    printf("to E, T, A, O, I, N ... to obtain possible plaintext.\n");

    return 0;
}
