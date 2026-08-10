#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Given 5x5 Playfair Matrix
char matrix[5][5] = {
    {'M', 'F', 'H', 'I', 'K'}, // 'I' and 'J' share a position
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

// Finds the coordinates of a given character in the matrix
void findPosition(char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I'; // Treat 'J' as 'I'
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (matrix[r][c] == ch || (matrix[r][c] == 'I' && ch == 'J')) {
                *row = r;
                *col = c;
                return;
            }
        }
    }
}

// Encrypts pair using Playfair rules
void encryptPair(char a, char b, char *c1, char *c2) {
    int r1, c1_pos, r2, c2_pos;
    findPosition(a, &r1, &c1_pos);
    findPosition(b, &r2, &c2_pos);

    // Rule 1: Same Row -> Shift right
    if (r1 == r2) {
        *c1 = matrix[r1][(c1_pos + 1) % 5];
        *c2 = matrix[r2][(c2_pos + 1) % 5];
    }
    // Rule 2: Same Column -> Shift down
    else if (c1_pos == c2_pos) {
        *c1 = matrix[(r1 + 1) % 5][c1_pos];
        *c2 = matrix[(r2 + 1) % 5][c2_pos];
    }
    // Rule 3: Rectangle -> Swap columns
    else {
        *c1 = matrix[r1][c2_pos];
        *c2 = matrix[r2][c1_pos];
    }
}

int main() {
    char input[] = "Must see you over Cadogan West. Coming at once.";
    char cleanText[200] = "";
    char preparedText[200] = "";
    char ciphertext[200] = "";

    // 1. Clean input (keep only uppercase letters, treat J as I)
    int len = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            char ch = toupper(input[i]);
            if (ch == 'J') ch = 'I';
            cleanText[len++] = ch;
        }
    }
    cleanText[len] = '\0';

    // 2. Prepare digram pairs (insert 'X' between duplicate letters in a pair)
    int pLen = 0;
    for (int i = 0; i < len; i++) {
        preparedText[pLen++] = cleanText[i];
        if (i + 1 < len) {
            if (cleanText[i] == cleanText[i + 1]) {
                preparedText[pLen++] = 'X';
            } else {
                preparedText[pLen++] = cleanText[++i];
            }
        }
    }
    // Append 'X' if odd length
    if (pLen % 2 != 0) {
        preparedText[pLen++] = 'X';
    }
    preparedText[pLen] = '\0';

    // 3. Encrypt in pairs
    for (int i = 0; i < pLen; i += 2) {
        encryptPair(preparedText[i], preparedText[i + 1], &ciphertext[i], &ciphertext[i + 1]);
    }
    ciphertext[pLen] = '\0';

    printf("Original Message: %s\n", input);
    printf("Prepared Text:   %s\n", preparedText);
    printf("Ciphertext:      %s\n", ciphertext);

    return 0;
}
