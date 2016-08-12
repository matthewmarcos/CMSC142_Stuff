#include <stdio.h>
#include <stdlib.h>

void merge(int a[], int lower, int mid, int upper) {
    int *temp, i, j, k;

    temp = (int *)malloc((upper - lower + 1) * sizeof(int));

    for(i = 0, j = lower, k = mid + 1; j <= mid || k <= upper; i++) {
        // temp[i] = ( <= a[k])? a[j++] : a[k++];
        int x = (j <= mid) && ((k == upper + 1) || (a[j] <= a[k]));

        temp[i] = (x)? a[j++] : a[k++];
    }

    for(i = 0, j = lower; j <= upper ; i++, j++) {
        a[j] = temp[i];
    }
    
    free(temp);
}

void merge_sort(int a[], int lower, int upper) {
    int mid, i;

    if(upper - lower > 0) {
        mid = (lower + upper) / 2;
        merge_sort(a, lower, mid);
        merge_sort(a, mid + 1, upper);
        merge(a, lower, mid, upper);
    }
}

int main() { 
    int i;
    int a[5] = {4, 3, 2, 1, 0};

    printf("Unsorted: \n");
    for(i = 0 ; i < 5; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    merge_sort(a, 0, 4);

    printf("Sorted: \n");
    for(i = 0 ; i < 5; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");


}