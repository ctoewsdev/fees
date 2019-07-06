#include <stdio.h>
#include <stdlib.h>
#include "memberlist.h"

void list_init(member_list *mlist){
    *mlist = 0;
}

void list_clear(member_list *mlist){
    membernode *p, *q;
    for(p=*mlist; p !=0; p=q){
        q = p-> next;
        free(p);
    }
    list_init(mlist);
}

int list_insert(member_list *mlist, const member *pmem){ 
    membernode *newnode = malloc(sizeof(membernode));

    if (newnode == 0)
      return 0;
  
    newnode->data = *pmem;
    newnode->next = *mlist;
    *mlist = newnode;
    return 1;  
}