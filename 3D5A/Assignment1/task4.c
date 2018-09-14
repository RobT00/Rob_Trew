//Robert Trew - 15315527
//27-10-2017
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFERSIZE 20
#define TEST_SIZE 120001

int COLLISIONS = 0;
int METHOD = 0;
int NUM_TERMS = 0;

typedef struct People {
    int p_id;
    char d_id[BUFFERSIZE];
    char sname[BUFFERSIZE];
    char fname[BUFFERSIZE];
    int age;
    char p_type[BUFFERSIZE];
    char gen[BUFFERSIZE];
    char nat[BUFFERSIZE];
    char rel[BUFFERSIZE];
    char job[BUFFERSIZE];
    struct People *next_p;
}People;

typedef struct Element {
    struct People *person;
}Element;

void read_first_line(FILE *pFile, char *buffer);
int hash1(char *s);
int hash2(char *s);
char* csv_reader(FILE *f, char* buff);
void add_to(FILE *f, Element *elem);
Element* look_for(Element *elem, char *x, int *y);
People* get_person(FILE *f);
void add_p(Element *n, FILE *f, int *z);
char* read_in(char *s);
void p_print(People *p);
void add_node(People **n, People *x);

int main(int argv, char *argc[]) { 
    FILE *f;
    f = fopen("people.csv", "r");
    //f = fopen("truncated.csv", "r");
    if (f == NULL) {
        puts("Failed to open file");
        return -1;
    }
    Element hashes[TEST_SIZE];
    Element* hp = hashes;
    char line[300];
    read_first_line(f, line);
    char temp[BUFFERSIZE];
    int i = 0;
    
    do {
    printf("Please choose a hashing method: 1, 2\n");
    read_in(temp);
    METHOD = atoi(temp);
    }while(METHOD != 1 && METHOD != 2);

    while(!feof(f)){
        add_to(f, hashes);
    }
    printf(" ");
    printf("Capacity = %d\n", TEST_SIZE);
    printf("Number of terms = %d\n", NUM_TERMS);
    printf("Collisions = %d\n", COLLISIONS);
    
    puts("SEARCHING");
    puts("Enter 'quit' to exit:");
    read_in(temp);
    i = 0;
    while(strcmp(temp, "quit") != 0) {
        if (look_for(hp, temp, &i)){
            printf("%s", line);
            p_print(hashes[i].person);
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

People* get_person(FILE *f){
    char b[256];
    People *new_p = (People*)malloc(sizeof(People));
    new_p->p_id = atoi(csv_reader(f, b));
    strcpy(new_p->d_id, csv_reader(f, b));
    strcpy(new_p->sname, csv_reader(f, b));
    strcpy(new_p->fname, csv_reader(f, b));
    new_p->age = atoi(csv_reader(f, b));
    strcpy(new_p->p_type, csv_reader(f, b));
    strcpy(new_p->gen, csv_reader(f, b));
    strcpy(new_p->nat, csv_reader(f, b));
    strcpy(new_p->rel, csv_reader(f, b));
    strcpy(new_p->job, csv_reader(f, b));
    return new_p;
}

Element* look_for(Element *elem, char *x, int *y){
    static int p = 0;
    int q = 0;
    int i;

    if (METHOD == 1 && *y == 0) {i = hash1(x);}
    else if (METHOD == 2 || METHOD ==3 && *y == 0) {i = hash2(x);}
    else {i = *y;}

    while (elem[i].person) {
        if (strcmp(elem[i].person->sname, x) == 0) {
            if (!q) {q=!q;}
            break;
        }
        else {
            i++;
            if (i >= TEST_SIZE - 1) {
                puts("hereh");
                i = i % TEST_SIZE;
            }
            if (*y != 0) {COLLISIONS++;}
        }
    }

    *y = i;
    if (q) {return(&elem[i]);}
    else {return(NULL);}
}

char* read_in(char *s){ //fgets without newline
    char *a;
    a = fgets(s, BUFFERSIZE, stdin);
    if(!a) {return a;}
    
    if (s[strlen(s) - 1] == '\n') {s[strlen(s) - 1] = '\0';}

    return s;
}

void add_to(FILE *f, Element *elem){
    People *temp;
    temp = (People*)malloc(sizeof(People));
    int x;
    Element p;
    temp = get_person(f);
    if (METHOD == 1) {x = hash1(temp->sname);}
    else {x = hash2(temp->sname);}
    int i;
    if (look_for(elem, temp->sname, &x)) {//Surname already in list
        add_node(&elem[x].person, temp);
    }
    else {//Surname not in list
        add_node(&elem[x].person, temp);
    }
    NUM_TERMS++;
    free(temp);
}

void add_node(People **n, People *x) {
    x->next_p = *n;
    *n = x;
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

void p_print(People *p) {
    int x = 0;
    char *a = p->sname;
    while (p) {
        printf("%d\t", p->p_id);
        printf("%s\t", p->d_id);
        printf("%s\t", p->sname);
        printf("%s\t", p->fname);
        printf("%d\t", p->age);
        printf("%s\t", p->p_type);
        printf("%s\t", p->gen);
        printf("%s\t", p->nat);
        printf("%s\t", p->rel);
        printf("%s\t\n", p->job);
        p = p->next_p;
        x++;
    }
    printf("\nFound '%s' %d times\n", a, x);
}