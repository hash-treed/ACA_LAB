#include <stdio.h>

#define N 100000

int A[N], B[N], C[N];

int main() {
    // Initialize arrays
    int i;
    for (i = 0; i < N; i++) {
        A[i] = i;
        B[i] = i * 2;
    }

    // UNROLL FACTOR 1x (Baseline - No Unrolling)
    for (i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
    }

    printf("Result 1x: %d\n", C[N-1]);
    return 0;
}
