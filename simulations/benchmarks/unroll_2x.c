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

    // UNROLL FACTOR 2x
    for (i = 0; i < N; i += 2) {
        C[i] = A[i] + B[i];
        C[i+1] = A[i+1] + B[i+1];
    }

    printf("Result 2x: %d\n", C[N-1]);
    return 0;
}
