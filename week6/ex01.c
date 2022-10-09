#include <stdio.h>
#include <stdlib.h>

int *A;
int n;

int rFE(int k, int l, int r) {
    if(l>r) {
        return r;
    }
    int mid = (l + r) / 2;
    if (k == A[mid]) {
        return mid;
    }
    else if(l == r){
        int index;
        if (A[mid] > k) {
            index = mid - 1;
        }
        else {
            index = n;
        }
        if(index < 0) index = 0;

        return index;
    }

    else if (k < A[mid]) {
        return rFE(k, l, mid - 1);
    }
    else {
        return rFE(k, mid + 1, r);
    }
}

int findElement(int k) {
    return rFE(k,0,n-1);
}

int main() {

    int k,index;
    scanf("%d %d", &n,&k);

    A = (int *) malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    index = findElement(k);
    printf("%d", index);
    return 0;
}

