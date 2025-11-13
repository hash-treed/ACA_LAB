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

    // UNROLL FACTOR 8x
    for (i = 0; i < N; i += 8) {
        C[i] = A[i] + B[i];
        C[i+1] = A[i+1] + B[i+1];
        C[i+2] = A[i+2] + B[i+2];
        C[i+3] = A[i+3] + B[i+3];
        C[i+4] = A[i+4] + B[i+4];
        C[i+5] = A[i+5] + B[i+5];
        C[i+6] = A[i+6] + B[i+6];
        C[i+7] = A[i+7] + B[i+7];
    }

    printf("Result 8x: %d\n", C[N-1]);
    return 0;
}
