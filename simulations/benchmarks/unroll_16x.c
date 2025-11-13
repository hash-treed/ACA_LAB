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

    // UNROLL FACTOR 16x
    for (i = 0; i < N; i += 16) {
        C[i] = A[i] + B[i];
        C[i+1] = A[i+1] + B[i+1];
        C[i+2] = A[i+2] + B[i+2];
        C[i+3] = A[i+3] + B[i+3];
        C[i+4] = A[i+4] + B[i+4];
        C[i+5] = A[i+5] + B[i+5];
        C[i+6] = A[i+6] + B[i+6];
        C[i+7] = A[i+7] + B[i+7];
        C[i+8] = A[i+8] + B[i+8];
        C[i+9] = A[i+9] + B[i+9];
        C[i+10] = A[i+10] + B[i+10];
        C[i+11] = A[i+11] + B[i+11];
        C[i+12] = A[i+12] + B[i+12];
        C[i+13] = A[i+13] + B[i+13];
        C[i+14] = A[i+14] + B[i+14];
        C[i+15] = A[i+15] + B[i+15];
    }

    printf("Result 16x: %d\n", C[N-1]);
    return 0;
}
