#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Fixed: Required for memset, memcpy, and string functions
#include <time.h>

#define BLOCK_SIZE 16

void simple_cipher_encrypt(const unsigned char *in, unsigned char *out, const unsigned char *key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        out[i] = in[i] ^ key[i]; // Simulated substitution block operation
    }
}

void task2_benchmark_modes() {
    int data_size = 10 * 1024 * 1024; // 10 MB payload
    unsigned char *data = (unsigned char *)malloc(data_size);
    unsigned char *output = (unsigned char *)malloc(data_size);

    if (!data || !output) {
        printf("Memory allocation failed!\n");
        return;
    }

    unsigned char key[BLOCK_SIZE] = "0123456789ABCDEF";
    unsigned char iv[BLOCK_SIZE]  = "FEDCBA9876543210";

    memset(data, 0xAA, data_size); // Clear/initialize dataset memory

    printf("=== [Task 2] Block Cipher Modes Performance (10 MB Payload) ===\n");

    // 1. ECB Mode
    clock_t start = clock();
    for (int i = 0; i < data_size; i += BLOCK_SIZE) {
        simple_cipher_encrypt(data + i, output + i, key);
    }
    printf("ECB Execution Time : %.5f sec\n", (double)(clock() - start) / CLOCKS_PER_SEC);

    // 2. CBC Mode (Chained IV handling)
    start = clock();
    unsigned char feedback[BLOCK_SIZE];
    memcpy(feedback, iv, BLOCK_SIZE);

    for (int i = 0; i < data_size; i += BLOCK_SIZE) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            data[i + j] ^= feedback[j];
        }
        simple_cipher_encrypt(data + i, output + i, key);
        memcpy(feedback, output + i, BLOCK_SIZE);
    }
    printf("CBC Execution Time : %.5f sec\n", (double)(clock() - start) / CLOCKS_PER_SEC);

    // 3. CFB Mode (Cipher Feedback)
    start = clock();
    memcpy(feedback, iv, BLOCK_SIZE);
    unsigned char cipher_out[BLOCK_SIZE];

    for (int i = 0; i < data_size; i += BLOCK_SIZE) {
        simple_cipher_encrypt(feedback, cipher_out, key);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            output[i + j] = data[i + j] ^ cipher_out[j];
        }
        memcpy(feedback, output + i, BLOCK_SIZE);
    }
    printf("CFB Execution Time : %.5f sec\n", (double)(clock() - start) / CLOCKS_PER_SEC);

    // 4. OFB Mode (Output Feedback)
    start = clock();
    memcpy(feedback, iv, BLOCK_SIZE);

    for (int i = 0; i < data_size; i += BLOCK_SIZE) {
        simple_cipher_encrypt(feedback, feedback, key);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            output[i + j] = data[i + j] ^ feedback[j];
        }
    }
    printf("OFB Execution Time : %.5f sec\n", (double)(clock() - start) / CLOCKS_PER_SEC);

    free(data);
    free(output);
}

int main() {
    task2_benchmark_modes();
    return 0;
}
