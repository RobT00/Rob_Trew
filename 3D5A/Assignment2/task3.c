//Robert Trew - 15315527
//17-11-2017
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFERSIZE 60
#define TOP 10

const int SIZE = 18625;
const int RUN = 32;

typedef struct Game {
    char title[BUFFERSIZE];
    char platform[BUFFERSIZE];
    int score;
    int year;
}Game;

//QS method from http://www.geeksforgeeks.org/quick-sort/
//TimSort method from http://www.geeksforgeeks.org/timsort/

void tims_hl(Game a[]);
void ins_s (Game a[], int l, int h);
void merge (Game a[], int l, int m, int h);
int min(int a, int b);
void read_first_line(FILE *pFile, char *buffer);
char* csv_reader(FILE *f, char* buff);
void p_print(Game *g);
Game* get_game(FILE *f, Game *g);
void qs_hl(Game a[], int l, int h);
int partition(Game a[], int l, int h);
void swap(Game *x, Game *y);
//int rand_range(int l, int h);
char* read_in(char *s);

int main (int argv, char *argc[]) {
    FILE *f;
    char line[100], temp[4];
    int i = 0;
    f = fopen("ign.csv", "r");
    if (!f) {
        puts("Failed to open file");
        return -1;
    }
    read_first_line(f, line);
    Game g[SIZE];
    while (!feof(f) && i < SIZE) {get_game(f, &g[i]); i++;}
    do {
    printf("Enter 1 for TimSort or 2 for QuickSort: \n");
    read_in(temp);
    i = atoi(temp);
    }while(i != 1 && i != 2);
    if (i == 2) {qs_hl(g, 0, (sizeof(g)/sizeof(g[0])));}
    else {tims_hl(g);}
    printf("%s", line);
    p_print(g);
    return 0;
}

void read_first_line(FILE *pFile, char *buffer) {
    int i = 0;
    char c;

    do {
        c = fgetc(pFile);
        if (c == ',')
            buffer[i] = '\t';
        else {
            buffer[i] = c;
        }
        i++;
    }while(c != '\n');
    buffer[i] = '\0';
}

char* csv_reader(FILE *f, char *buff){
    int i = 0;
    int q = 0;
    for(;;) {
        buff[i] = fgetc(f);
        if(buff[i] == '"') {
            q=!q;
            buff[i] = fgetc(f);
        }
        if(buff[i] == ',' && !q) {break;}
        if(feof(f) || buff[i] == '\n' || buff[i] == '\r') {break;}
        i++;
    }
    if (buff[i] == '\r') {fgetc(f);}
    buff[i] = '\0';
    return buff;    
}

Game* get_game(FILE *f, Game *g) {
    char b[256];
    strcpy(g->title, csv_reader(f, b));
    strcpy(g->platform, csv_reader(f, b));
    g->score = atoi(csv_reader(f, b));
    g->year = atoi(csv_reader(f, b));
    return g;
}

void ins_s (Game a[], int l, int h) {
    int i, j;
    Game temp;
    for (i = l + 1; i <= h; i++) {
        temp = a[i];
        j = i - 1;
        while ((a[j].score < temp.score) && (j >= l)) {
            a[j + 1] = a[j];
            j--;
        }
        a[j+1] = temp;
    }
}

void merge (Game a[], int l, int m, int h) {
    int l1, l2, i, j, k;
    l1 = m - l + 1;
    l2 = h - m;
    Game left[l1], right[l2];
    for (i = 0; i < l1; i++) {left[i] = a[l + i];}
    for (i = 0; i < l2; i++) {right[i] = a[m + 1 + i];}
    i= 0;
    j = 0;
    k = l;
    while ((i < l1) && j < l2) {
        if(left[i].score >= right[j].score) {a[k] = left[i]; i++;}
        else {a[k] = right[j]; j++;}
        k++;
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

void tims_hl(Game a[]) {
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

void qs_hl(Game a[], int l, int h) {
    if (l < h) {
        int pi = partition(a, l, h);

        qs_hl(a, l, (pi - 1));
        qs_hl(a, (pi + 1), h);
    }
}

int partition(Game a[], int l, int h) {
    Game piv = a[h]; //pivot
    int i = (l -1); //index of smaller element
    int j;
    for (j = l; j <= (h-1); j++) {
        //If curr elem <= pivot
        if (a[j].score >= piv.score) {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[h]);
    return(i + 1);
}

void swap(Game *x, Game *y) {
    Game z = *x;
    *x = *y;
    *y = z;
}

/*int rand_range (int l, int h) {
    int r;
    int range = 1 + h - l;
    int buckets = RAND_MAX / range;
    int limit = buckets * range;

    do {
        r = rand();
    }while (r >= limit);

    return (l + (r / buckets));
}*/

void p_print(Game g[]) {
    int i;
    for (i = 0; i < TOP; i++) {
        printf("%s\t", g[i].title);
        printf("%s\t", g[i].platform);
        printf("%d\t", g[i].score);
        printf("%d\t\n", g[i].year);
    }
    printf("\n");
}

int min(int a, int b){
    if (a < b) {return a;}
    else {return b;}
}

char* read_in(char *s){ //fgets without newline
    char *a;
    a = fgets(s, BUFFERSIZE, stdin);
    if(!a) {return a;}
    
    if (s[strlen(s) - 1] == '\n') {s[strlen(s) - 1] = '\0';}

    return s;
}
