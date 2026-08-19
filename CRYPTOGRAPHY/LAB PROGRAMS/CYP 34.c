#include <stdio.h>
#include <string.h>

void pad_message(const unsigned char *in, int len, unsigned char *out, int *out_len, int block_size) {
    memcpy(out, in, len);
    int pad_needed = block_size - (len % block_size);

    // Add bit '1' (0x80)
    out[len] = 0x80;

    // Add trailing '0's
    for (int i = 1; i < pad_needed; i++) {
        out[len + i] = 0x00;
    }
    *out_len = len + pad_needed;
}

int main() {
    unsigned char msg_full[8] = {'A','B','C','D','E','F','G','H'}; // 8 bytes (full block)
    unsigned char padded[16];
    int padded_len = 0;

    pad_message(msg_full, 8, padded, &padded_len, 8);

    printf("Original Length: 8 bytes\n");
    printf("Padded Length: %d bytes (Mandatory extra padding block included)\n", padded_len);
    printf("Hex Output: ");
    for (int i = 0; i < padded_len; i++) {
        printf("%02X ", padded[i]);
    }
    printf("\n");

    return 0;
}
