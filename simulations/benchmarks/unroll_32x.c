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

    // UNROLL FACTOR 32x
    for (i = 0; i < N; i += 32) {
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
        C[i+16] = A[i+16] + B[i+16];
        C[i+17] = A[i+17] + B[i+17];
        C[i+18] = A[i+18] + B[i+18];
        C[i+19] = A[i+19] + B[i+19];
        C[i+20] = A[i+20] + B[i+20];
        C[i+21] = A[i+21] + B[i+21];
        C[i+22] = A[i+22] + B[i+22];
        C[i+23] = A[i+23] + B[i+23];
        C[i+24] = A[i+24] + B[i+24];
        C[i+25] = A[i+25] + B[i+25];
        C[i+26] = A[i+26] + B[i+26];
        C[i+27] = A[i+27] + B[i+27];
        C[i+28] = A[i+28] + B[i+28];
        C[i+29] = A[i+29] + B[i+29];
        C[i+30] = A[i+30] + B[i+30];
        C[i+31] = A[i+31] + B[i+31];
    }

    printf("Result 32x: %d\n", C[N-1]);
    return 0;
}
