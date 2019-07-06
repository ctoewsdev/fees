#ifndef RECORD_H
#define RECORD_H
#define IDSIZE 6
#define NAMESIZE 20

typedef struct {
    char last[NAMESIZE];
    char first[NAMESIZE];
} name;

typedef struct {
    char id[IDSIZE];
    name name;
    double fee;
} member;


#endif