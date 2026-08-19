#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Expected English letter frequencies (%)
const float ENG_FREQ[26] = {
    8.17, 1.49, 2.78, 4.25, 12.70, 2.23, 2.01, 6.09, 6.97, 0.15, 0.77, 4.03, 2.41,
    6.75, 7.51, 1.93, 0.09, 5.98, 6.32, 9.05, 2.75, 0.98, 2.36, 0.15, 1.97, 0.07
};

typedef struct {
    int key;
    float score;
    char text[500];
} Candidate;

int compare_candidates(const void *a, const void *b) {
    float diff = ((Candidate *)b)->score - ((Candidate *)a)->score;
    return (diff > 0) ? 1 : (diff < 0) ? -1 : 0;
}

float score_text(const char *text) {
    int counts[26] = {0};
    int total = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            counts[toupper(text[i]) - 'A']++;
            total++;
        }
    }
    if (total == 0) return 0.0f;

    float score = 0.0f;
    for (int i = 0; i < 26; i++) {
        float observed = ((float)counts[i] / total) * 100.0f;
        score -= (observed - ENG_FREQ[i]) * (observed - ENG_FREQ[i]); // Negative MSE score
    }
    return score;
}

void additive_frequency_attack(const char *ct, int top_n) {
    Candidate candidates[26];
    int len = strlen(ct);

    for (int k = 0; k < 26; k++) {
        candidates[k].key = k;
        for (int i = 0; i < len; i++) {
            if (isalpha(ct[i])) {
                char base = isupper(ct[i]) ? 'A' : 'a';
                candidates[k].text[i] = ((ct[i] - base - k + 26) % 26) + base;
            } else {
                candidates[k].text[i] = ct[i];
            }
        }
        candidates[k].text[len] = '\0';
        candidates[k].score = score_text(candidates[k].text);
    }

    qsort(candidates, 26, sizeof(Candidate), compare_candidates);

    printf("\n--- Top %d Decryption Candidates ---\n", top_n);
    for (int i = 0; i < top_n && i < 26; i++) {
        printf("Rank %d (Key Shift = %2d): %s\n", i + 1, candidates[i].key, candidates[i].text);
    }
}

int main() {
    char ciphertext[] = "KHOOR ZRUOG"; // "HELLO WORLD" shifted by 3
    int top_n = 5;

    printf("Ciphertext: %s\n", ciphertext);
    additive_frequency_attack(ciphertext, top_n);

    return 0;
}
