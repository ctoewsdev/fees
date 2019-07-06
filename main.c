/* CML $gcc -ansi -pedantic -W -Wall -Werror *.c  */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "member.h"
#include "io.h"
#include "memberlist.h"
#include "sort.h"

#define LINESIZE  1024
#define MINWORDSINMEMBER 4
#define IDINTEGERS 5

int is_valid_id(const char[]);
int parse_member(const char*, member*);
void print_member(const member*);

int main (void) {
    char buffer[LINESIZE];
    char tmpbuffer[LINESIZE]; 
    member_list memlist;
    member rec;
    membernode *p;

    /*initialize member list*/
    list_init(&memlist);
   
    /*read input to a max of LINESIZE - 1*/
    while(fgets(buffer, LINESIZE, stdin)){
        if (sscanf(buffer, "%s", tmpbuffer) == 1){
            if(parse_member(buffer, &rec)){
                list_insert(&memlist, &rec);
            }
        } else 
            printf("tmp buffer is NOT ok");
    }

    printf("\n***********************************\n");
    printf("  SUMMARY OF MEMBER FEES OWING\n");
    printf("***********************************\n");

    printf("\n***************BY FEE**************\n");
    sort_by_fee(&memlist);
    printf("  FEE    LAST   FIRST    ID\n");
    for (p = memlist; p != 0; p = p->next)
        print_member(&p->data);
      
    printf("\n************BY LAST NAME***********\n");
    sort_by_lname(&memlist);
    printf("  FEE    LAST   FIRST    ID\n");
    for (p = memlist; p != 0; p = p->next)
        print_member(&p->data);
            
    printf("\n************BY FIRST NAME***********\n");
    sort_by_fname(&memlist);
    printf("  FEE    LAST   FIRST    ID\n");
    for (p = memlist; p != 0; p = p->next)
        print_member(&p->data);
            
    printf("\n****************BY ID***************\n");
    sort_by_id(&memlist);
    printf("  FEE    LAST   FIRST    ID\n");
    for (p = memlist; p != 0; p = p->next)
        print_member(&p->data);
 
    list_clear(&memlist);
    
    return 0;
}


int parse_member(const char *s, member *prec){
    int r;

    r = sscanf(s, "%s %s %s %lf", prec->id, prec->name.first, prec->name.last, &prec->fee);
       
    if(r < MINWORDSINMEMBER)
        return 0;
    if(!is_valid_id(prec->id))
        return 0;

    return 1;
}

void print_member(const member *prec) {
    member rec = *prec;
    printf("$%.2f  %s,  %s  (%s)\n", prec->fee,  rec.name.last, rec.name.first, prec->id);
}

int is_valid_id(const char s[]){
    char ch;
    int d;
    int totalints = 0;
    sscanf(s, "%c %d", &ch, &d);
    if(ch == 'z' || ch == 'Z'){
        toupper(s[0]);
        while(d != 0) {
            d /= 10;
            ++totalints;
        }
        if(totalints == IDINTEGERS)
            return 1;
    }  
    return 0;
} 