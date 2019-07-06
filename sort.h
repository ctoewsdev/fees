#ifndef SORT_H
#define SORT_H
#include "memberlist.h"

void sort_by_fee(member_list*);
void sort_by_lname(member_list*);
void sort_by_fname(member_list*);
void sort_by_id(member_list*);
void swapnode(membernode*, membernode*);

#endif