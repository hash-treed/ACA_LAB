#include <stdio.h>
int A[10000];
int main() {
    int i;
    for(i = 0; i < 10000; i++) {
        A[i]=i+(i-1);
    }
     printf("Result: %d\n", A[10000 - 1]);
    return 0;
}

