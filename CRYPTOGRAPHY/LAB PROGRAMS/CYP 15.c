#include <stdio.h>
#include <string.h>
#include <ctype.h>

int score(char text[]) {
    char common[] = "ETAOINSHRDLU";
    int s = 0;

    for(int i = 0; text[i] != '\0'; i++) {
        for(int j = 0; j < 12; j++) {
            if(toupper(text[i]) == common[j])
                s++;
        }
    }
    return s;
}

int main() {
    char cipher[500], plain[500];
    char result[10][500];
    int scores[10];
    int shift, i, j, k, sc;

    for(i = 0; i < 10; i++)
        scores[i] = -1;

    printf("Enter ciphertext (UPPERCASE): ");
    fgets(cipher, sizeof(cipher), stdin);

    for(shift = 0; shift < 26; shift++) {

        k = 0;

        for(i = 0; cipher[i] != '\0'; i++) {
            if(cipher[i] >= 'A' && cipher[i] <= 'Z')
                plain[k++] = ((cipher[i]-'A'-shift+26)%26)+'A';
            else
                plain[k++] = cipher[i];
        }

        plain[k] = '\0';

        sc = score(plain);

        for(j = 0; j < 10; j++) {
            if(sc > scores[j]) {

                for(int m = 9; m > j; m--) {
                    scores[m] = scores[m-1];
                    strcpy(result[m], result[m-1]);
                }

                scores[j] = sc;
                strcpy(result[j], plain);
                break;
            }
        }
    }

    printf("\nTop 10 Possible Plaintexts:\n");

    for(i = 0; i < 10; i++) {
        if(scores[i] >= 0)
            printf("%d. %s (Score: %d)\n",
                   i+1, result[i], scores[i]);
    }

    return 0;
}
