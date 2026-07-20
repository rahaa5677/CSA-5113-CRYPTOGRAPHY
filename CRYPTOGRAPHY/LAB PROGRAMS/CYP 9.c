#include <stdio.h>

char key[5][5] = {
    {'M','O','N','A','R'},
    {'C','H','Y','B','D'},
    {'E','F','G','I','K'},
    {'L','P','Q','S','T'},
    {'U','V','W','X','Z'}
};

void findPos(char ch, int *r, int *c) {
    if (ch == 'J') ch = 'I';

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (key[i][j] == ch) {
                *r = i;
                *c = j;
            }
}

int main() {
    char a, b;
    int r1, c1, r2, c2;

    printf("Enter two cipher letters: ");
    scanf(" %c%c", &a, &b);

    findPos(a, &r1, &c1);
    findPos(b, &r2, &c2);

    if (r1 == r2) {
        printf("Plaintext: %c%c",
               key[r1][(c1 + 4) % 5],
               key[r2][(c2 + 4) % 5]);
    }
    else if (c1 == c2) {
        printf("Plaintext: %c%c",
               key[(r1 + 4) % 5][c1],
               key[(r2 + 4) % 5][c2]);
    }
    else {
        printf("Plaintext: %c%c",
               key[r1][c2],
               key[r2][c1]);
    }

    return 0;
}
