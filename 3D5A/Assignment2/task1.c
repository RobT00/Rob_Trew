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
//QS method from http://www.geeksforgeeks.org/quick-sort/
void swap(int *x, int *y);
int partition(int a[], int l, int h);
void qs_lh(int a[], int l, int h);
void arr_print(int a[]);
void fill(int *a, int c);
void report(int t, int a[]);
void r_z(int *x, int* y);
int rand_range(int l, int h);

int main (int argv, char *argc[]) {
    int arr[10], arr1[SIZE];
    int i;
    
    fill(arr, 0);
    qs_lh(arr, 0, 9);
    report(0, arr);

    printf("Running profile tests with %d elements\n\n", SIZE);
    for (i = 1; i <= 5; i++) {
        fill(arr1, i);
        clock_t start = clock() * 1000;
        qs_lh(arr1, 0, (SIZE - 1));
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
        case 0: for (i = 0; i < 10; i++) {
                    a[i] = rand() % 54000;
                }
                break;
        case 1: for (i = 0; i < (SIZE); i++) {
                    a[i] = i;
                }
                for (i = 0; i < (SIZE); i++) {
                    r = a[i];
                    j = rand() % SIZE;
                    a[i] = a[j];
                    a[j] = r;
                }
                break;
        case 2: for (i = 0; i < (SIZE); i++) {
                    a[i] = rand() % 100000;
                }
                break;
        case 3: for (i = 0; i < (SIZE); i++) {
                    a[i] = i;
                }
                break;
        case 4: j = 0;
                for (i = (SIZE); i >= 0; i--) {
                    a[j] = i;
                    j++;
                }
                break;
        default: j = 3;
                for (i = 0; i < (SIZE); i++) {
                    a[i] = j;
                }
                break;
    }
}

int partition(int a[], int l, int h) {
    /*int piv = a[h];
    int i = l - 1;
    int j = h;
    for (;;) {
        do {
            i--;
        }while (a[i] < piv);
        do {
            j--;
        }while (a[j] > piv);
        COMPS++;
        if (i >= j) {
            swap(&a[j + 1], &a[h]);
            return j;
        }
    }
    swap(&a[i], &a[j]);*/
    int piv = a[h]; //pivot
    int i = (l -1); //index of smaller element
    int j;
    for (j = l; j <= (h-1); j++) {
        //If curr elem <= pivot
        COMPS++;
        if (a[j] < piv) {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[h]);
    return(i + 1);
}

void swap(int *x, int*y) {
    int z = *x;
    *x = *y;
    *y = z;
    SWAPS++;
}

void qs_lh(int a[], int l, int h) {
    /*if (l < h) {
        int piv_ind = rand_range(l, h);
        int piv = a[piv_ind];
        a[piv_ind] = a[h];
        a[h] = piv;
        int i = l - 1;
        int j = h;
        do {
            do{
                i++;
                COMPS;;
            } while (a[i] < piv);
            do {
                j--;
                COMPS++;
            } while ((a[j] > piv) && (j > l));
            if (i < j) {swap(&a[i], &a[j]);}
        } while (i < j);
        a[h] = a[i];
        a[i] = piv;
        qs_lh (a, l, i - 1);
        qs_lh(a, i + 1, h);
    }*/

    /*if (l < h) {
        int s = l + 1;
        int r = h;
        int p = a[s];
        while (s < r) {
            if (a[s] <= p) {s++;}
            else if (a[r] >= p) {r--;}
            else {swap(&a[s], &a[r]);}
            COMPS++;
        }
        if (a[s] < p) {
            swap(&a[s], &a[l]);
            s--;
        }
        else {
            s--;
            swap(&a[s], &a[l]);
        }
        qs_lh(a, l, s);
        qs_lh(a, r, h);
    }*/
    if (l < h) {
        int pi = partition(a, l, h);

        qs_lh(a, l, (pi - 1));
        qs_lh(a, (pi + 1), h);
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
    for (i = 0; i < (SIZE - 2); i++) {
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

int rand_range (int l, int h) {
    int r;
    int range = 1 + h - l;
    int buckets = RAND_MAX / range;
    int limit = buckets * range;

    do {
        r = rand();
    }while (r >= limit);

    return (l + (r / buckets));
}