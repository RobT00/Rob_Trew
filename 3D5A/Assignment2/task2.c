//Robert Trew - 15315527
//17-11-2017
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

const int SIZE = 10000;
int SWAPS = 0;
int COMPS = 0;
float SEC = 0;
const int RUN = 42;

//TimSort method from http://www.geeksforgeeks.org/timsort/

void tims_lh(int a[]);
void ins_s (int a[], int l, int h);
void merge (int a[], int l, int m, int h);
void arr_print(int a[]);
void fill(int *a, int c);
void report(int t, int a[]);
void r_z(int *x, int* y);
int min(int a, int b);

int main (int argv, char *argc[]) {
    int arr[10], arr1[SIZE];
    int i;

    printf("Running profile tests with %d elements\n\n", SIZE);
    for (i = 1; i <= 5; i++) {
        fill(arr1, i);
        clock_t start = clock() * 1000;
        tims_lh(arr1);
        clock_t end = clock() * 1000;
        SEC = (end - start) / CLOCKS_PER_SEC;;
        report(i, arr1);
    }

    return 0;
}

void fill(int *a, int c) {
    time_t t;
    srand((unsigned) time(&t));
    int i, j, r;
    switch(c) {
        case 0: for (i = 0; i < 9; i++) {
                    a[i] = rand() % 54000;
                }
                break;
        case 1: for (i = 0; i < (SIZE - 1); i++) {
                    a[i] = i;
                }
                for (i = 0; i < (SIZE - 1); i++) {
                    r = a[i];
                    j = rand() % SIZE;
                    a[i] = a[j];
                    a[j] = r;
                }
                break;
        case 2: for (i = 0; i < (SIZE - 1); i++) {
                    a[i] = rand() % 100000;
                }
                break;
        case 3: for (i = 0; i < (SIZE - 1); i++) {
                    a[i] = i;
                }
                break;
        case 4: j = 0;
                for (i = (SIZE - 1); i >= 0; i--) {
                    a[j] = i;
                    j++;
                }
                break;
        default: j = 3;
                for (i = 0; i < (SIZE - 1); i++) {
                    a[i] = j;
                }
                break;
    }
}

void ins_s (int a[], int l, int h) {
    int i, temp, j;
    for (i = l + 1; i <= h; i++) {
        temp = a[i];
        j = i - 1;
        while ((a[j] > temp) && (j >= l)) {
            a[j + 1] = a[j];
            COMPS++;
            SWAPS++;
            j--;
        }
        a[j+1] = temp;
        SWAPS++;
    }
}

void merge (int a[], int l, int m, int h) {
    int l1, l2, i, j, k;
    l1 = m - l + 1;
    l2 = h - m;
    int left[l1], right[l2];
    for (i = 0; i < l1; i++) {left[i] = a[l + i];}
    for (i = 0; i < l2; i++) {right[i] = a[m + 1 + i];}
    i= 0;
    j = 0;
    k = l;
    while ((i < l1) && j < l2) {
        COMPS++;
        if(left[i] <= right[j]) {a[k] = left[i]; i++;}
        else {a[k] = right[j]; j++;}
        k++;
        SWAPS++;
    }
    while (i < l1) {
        a[k] = left[i];
        k++;
        i++;
    }
    while (j < l2) {
        a[k] = right[j];
        k++;
        j++;
    }
}

void tims_lh(int a[]) {
    int i, left, right, mid;
    for (i = 0; i < SIZE; i+=RUN) {ins_s(a, i, min((i + (RUN - 1)), (SIZE - 1)));}
    for (i = RUN; i < SIZE; i = 2*i) {
        for (left = 0; left < SIZE; left += 2*i) {
            //mid = left + i - 1;
            right = min((left + 2*i - 1), (SIZE - 1));
            mid = (left + right - 1)/2;
            merge(a, left, mid, right);
        }
    }
}

void arr_print(int a[]) {
    int i = 0;
    for (i; i < SIZE; i++) {
        printf("%d, ", a[i]);
    }
    printf("\n");
}

void report(int t, int a[]) {
    int b = 1;
    int i;
    for (i = 0; i < (SIZE - 1); i++) {
        if (a[i] > a[i+1]) {b!=b; break;}
    }
    if (!b) {
        printf("ERROR! Case %d, not sorted", t);
        return;
    }
    printf("TEST\t:\t");
    switch(t) {
        case 0: puts("Array size 10");
                printf("SORTED\t:\tY\n");
                printf("SWAPS\t:\t%d\n", SWAPS);
                printf("COMPS\t:\t%d\n", COMPS);
                break;
        case 1: puts("Unique random values");
                printf("SORTED\t:\tY\n");
                printf("SWAPS\t:\t%d\n", SWAPS);
                printf("COMPS\t:\t%d\n", COMPS);
                printf("TIME\t:\t%.3f ms\n", SEC);
                break;
        case 2: puts("Random values");
                printf("SORTED\t:\tY\n");
                printf("SWAPS\t:\t%d\n", SWAPS);
                printf("COMPS\t:\t%d\n", COMPS);
                printf("TIME\t:\t%.3f ms\n", SEC);        
                break;
        case 3: puts("Ascending sorted list");
                printf("SORTED\t:\tY\n");
                printf("SWAPS\t:\t%d\n", SWAPS);
                printf("COMPS\t:\t%d\n", COMPS);
                printf("TIME\t:\t%.3f ms\n", SEC); 
                break;
        case 4: puts("Descending sorted list");
                printf("SORTED\t:\tY\n");
                printf("SWAPS\t:\t%d\n", SWAPS);
                printf("COMPS\t:\t%d\n", COMPS);
                printf("TIME\t:\t%.3f ms\n", SEC); 
                break;
        case 5: puts("Uniform list");
                printf("SORTED\t:\tY\n");
                printf("SWAPS\t:\t%d\n", SWAPS);
                printf("COMPS\t:\t%d\n", COMPS);
                printf("TIME\t:\t%.3f ms\n", SEC); 
                break;
        default: puts("Case type not known!");
                break;
    }
    if (t !=5) {printf("\n");}
    r_z(&SWAPS, &COMPS);
}

void r_z(int *x, int *y) {
    *x = 0;
    *y = 0;
}

int min(int a, int b){
    if (a < b) {return a;}
    else {return b;}
}