//Robert Trew - 15315527
//27-10-2017
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ARRAY1 1450
#define ARRAY2 20
#define BUFFERSIZE 30
#define TEST_SIZE 103

int COLLISIONS = 0;
int METHOD = 3;
int NUM_TERMS = 0;

typedef struct Element {
    char name[BUFFERSIZE];
    int count;
}Element;

int hash1(char *s);
int hash2(char *s);
int hash3(int x);
char* csv_reader(FILE *f, char* buff);
void add_to(Element *elem, char *a);
Element* look_for(Element *elem, char *x, int *z, int *y);
char* read_in(char *s);

int main(int argv, char *argc[]) { 
    FILE *f;
    f = fopen("names.csv", "r");
    if (f == NULL) {
        puts("Failed to open file");
        return -1;
    }

    Element hashes[TEST_SIZE];
    Element* hp = hashes;
    char temp[BUFFERSIZE];
    int i = 0;

    while(!feof(f)){
        csv_reader(f, temp);
        add_to(hp, temp);
    }

    printf("Capacity = %d\n", TEST_SIZE);
    printf("Number of terms = %d\n", NUM_TERMS);
    printf("Collisions = %d\n", COLLISIONS);
    
    puts("SEARCHING");
    puts("Enter 'quit' to exit:");
    read_in(temp);
    while(strcmp(temp, "quit") != 0) {

        if (look_for(hp, temp, &i, &i)){
            printf("%s, was found %d times\n", temp, i);
        }
        else {printf("%s, was not found\n", temp);}

        read_in(temp);
        i = 0;
    }

    fclose(f);
    return 0;
}

int hash1(char *s) {
    int hash = 0;
    while(*s) {
        hash+=*s;
        s++;
    }
    hash = hash % TEST_SIZE;
    return hash;
}

int hash2(char *s) {
    int hash = 0;
    while(*s) {
        if (*s == 'o' || *s == 'O') {
            hash = hash + (*s * 31);
        }
        else if (*s == 'n' || *s == 'N') {
            hash = hash + (*s * 51);
        }
        else if (*s == 'v' || *s == 'V') {
            hash = hash + (*s / 7);
        }
        else if (*s == 'e' || *s == 'E') {
            hash = hash + (*s * 71);
        }
        else {
            hash+=*s;
        }
        s++;
    }
    hash = hash % TEST_SIZE;
    return hash;
}

int hash3(int x) {
    int hash = 0;
    hash = x * 8241;
    if (hash < 20000) {hash = abs(hash - 279);}
    else {
        hash = hash + 371;
    }
    hash = hash % TEST_SIZE;
    return hash;
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

Element* look_for(Element *elem, char *x, int *z, int *y){
    int q = 0;
    int i;

    if (METHOD == 1 && *y == 0) {i = hash1(x);}
    else if (METHOD == 2 || METHOD ==3 && *y == 0) {i = hash2(x);}
    else {i = *y;}

    while (elem[i].count != 0) {
        if (strcmp(elem[i].name, x) == 0) {q=!q; break;}
        else {
            i = hash3(i);
            if (*y != 0) {COLLISIONS++;}
        }
    }

    *y = i;
    *z = elem[i].count;
    if (q) {return(&elem[i]);}
    else {return(NULL);}
}

char* read_in(char *s){ //fgets without newline
    char *a;
    a = fgets(s, ARRAY2, stdin);
    if(!a) {return a;}
    
    if (s[strlen(s) - 1] == '\n') {s[strlen(s) - 1] = '\0';}

    return s;
}

void add_to(Element *elem, char *a){
    int x;
    if (METHOD == 1) {x = hash1(a);}
    else {x = hash2(a);}
    int i = 0;
    if (look_for(elem, a, &i, &x)) {
    }
    else {
        strcpy(elem[x].name, a);
        NUM_TERMS++;
    }
    elem[x].count++;
}