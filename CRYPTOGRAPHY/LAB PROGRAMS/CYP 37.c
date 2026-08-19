#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char ENGLISH_FREQ[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

typedef struct {
    char letter;
    int count;
} LetterFreq;

int compare_freq(const void *a, const void *b) {
    return ((LetterFreq *)b)->count - ((LetterFreq *)a)->count;
}

void monoalphabetic_attack(const char *ciphertext) {
    LetterFreq freq[26];
    for (int i = 0; i < 26; i++) {
        freq[i].letter = 'A' + i;
        freq[i].count = 0;
    }

    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            freq[toupper(ciphertext[i]) - 'A'].count++;
        }
    }

    qsort(freq, 26, sizeof(LetterFreq), compare_freq);

    char map[26];
    for (int i = 0; i < 26; i++) {
        map[freq[i].letter - 'A'] = ENGLISH_FREQ[i];
    }

    printf("\nDecrypted Plaintext (Statistical Frequency Mapping):\n");
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            char decrypted = map[toupper(ciphertext[i]) - 'A'];
            printf("%c", isupper(ciphertext[i]) ? decrypted : tolower(decrypted));
        } else {
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n");
}

int main() {
    char ciphertext[] = "GZAAC FBAVT";
    printf("Ciphertext: %s\n", ciphertext);
    monoalphabetic_attack(ciphertext);
    return 0;
}
