
#ifndef LIST_H
#define LIST_H
#include "member.h"

typedef struct membernode membernode;
struct membernode{
    member data;
    membernode *next;
};


typedef membernode *member_list;
void list_init(member_list*);
void list_clear(member_list*);
int list_insert(member_list*, const member*);

#endif