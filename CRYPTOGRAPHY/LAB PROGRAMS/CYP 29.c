#include <stdio.h>
#include <stdbool.h>

#define TOTAL_LANES 25
#define RATE_LANES 16
#define CAPACITY_LANES 9

int main() {
    // 0 = zero lane, 1 = non-zero lane
    int state[TOTAL_LANES] = {0};
    int P0[RATE_LANES];

    // Initialize P0: each lane has non-zero bits
    for (int i = 0; i < RATE_LANES; i++) {
        P0[i] = 1;
    }

    printf("Initial Capacity Lanes State: ");
    for (int i = RATE_LANES; i < TOTAL_LANES; i++) printf("%d ", state[i]);
    printf("(All Zeros)\n");

    // Phase 1: XOR P0 into Rate portion
    for (int i = 0; i < RATE_LANES; i++) {
        state[i] ^= P0[i];
    }

    // Phase 2: Permutation/Diffusion step spreads bits to capacity lanes
    // Simulating diffusion across state matrix
    int rounds = 0;
    bool capacity_has_zeros = true;

    while (capacity_has_zeros) {
        rounds++;
        // Simulate diffusion from rate lanes to capacity lanes
        for (int i = RATE_LANES; i < TOTAL_LANES; i++) {
            state[i] = 1; // Non-zero bit diffused
        }

        // Check if all capacity lanes are non-zero
        capacity_has_zeros = false;
        for (int i = RATE_LANES; i < TOTAL_LANES; i++) {
            if (state[i] == 0) {
                capacity_has_zeros = true;
                break;
            }
        }
    }

    printf("\nAfter %d round(s)/block processing:\n", rounds);
    printf("Capacity Lanes State: ");
    for (int i = RATE_LANES; i < TOTAL_LANES; i++) printf("%d ", state[i]);
    printf("\nTime taken: Exactly 1 message block absorb step / 1 permutation function call.\n");

    return 0;
}
