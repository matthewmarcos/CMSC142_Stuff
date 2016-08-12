// Names:
// Joseph Gabriel Adaoag
// Joseph Matthew Marcos

#include <stdio.h>
#include <stdlib.h>

int readArray(int **array, int *count, FILE *stream) {
    if(count == NULL || array == NULL || stream == NULL) {
        puts("Null arguments passed");
        return 1;
    }

    int *holder = NULL;
    int *tmp = NULL;
    int ii;
    int intHolder;
    for(ii = 0; !feof(stream); ii++) {
        if (!fscanf(stream, "%i ", &intHolder)) {
            if (!feof(stream)) {
                puts("Warning: Non-integer found, returning what was retrieved");
            }

            *array = holder;
            *count = ii;
            return 0;
            
        }

        if (ii == 0) {
            holder = malloc(sizeof(int));
            if(!holder) {
                puts("Error in allocating memory");
                return 2;
            }
        } else {
            tmp = realloc(holder, (ii+1)*sizeof(int));
            if (!tmp) {
                puts("Error in reallocating array");
                free(holder);
                return 3;
            }
            holder = tmp;
        }
        holder[ii] = intHolder;
    }


    *array = holder;
    *count = ii;
    return 1;
}

void merge(int a[], int lower, int mid, int upper) {
    int *temp, i, j, k;

    temp = (int *)malloc((upper - lower + 1) * sizeof(int));

    for(i = 0, j = lower, k = mid + 1; j <= mid || k <= upper; i++) {
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
    FILE *fp;

    fp = fopen("msort.in", "r");

    if (!fp) {
        puts("Unable to open file");
        return 1;
    }

    int *holder;
    int count = 0;
    readArray(&holder, &count, fp);

    fclose(fp);

    
    printf("Unsorted: \n");
    for(i = 0 ; i < count; i++) {
        printf("%d ", holder[i]);
    }
    printf("\n");

    merge_sort(holder, 0, count - 1);

    fp = fopen("msort.out", "w");
    if (!fp) {
        puts("Unable to open output file");
        return 1;
    }


    printf("Sorted: \n");
    for(i = 0 ; i < count; i++) {
        printf("%d ", holder[i]);
        fprintf(fp, "%d ", holder[i]);
    }
    printf("\n");
    fclose(fp);

}