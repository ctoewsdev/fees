#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LINESIZE  1024
#define IDSIZE 10
#define NAMESIZE 20
#define MINWORDSINRECORD 4
#define IDINTEGERS 5
#define BLOCK 2

typedef struct {
    char last[NAMESIZE];
    char first[NAMESIZE];
} name;

typedef struct {
    char id[IDSIZE];
    name name;
    double fee;
} record;

typedef struct node node;
struct node {
    record data;
    node *next;
} ;

typedef node *record_list;

int is_valid_id(const char[]);
int parse_record(const char*, record*);
void print_record(const record*);
void list_init(record_list*);
void list_clear(record_list*);
int list_insert(record_list*, const record*);
void sort_by_fee(record_list*);
void sort_by_lname(record_list*);
void sort_by_fname(record_list*);
void sort_by_id(record_list*);
void swap(node*, node*);

int main (void) {
    char buffer[LINESIZE];
    char tmpbuffer[LINESIZE]; 
    record_list reclist;
    record rec;
    node *p;

    /*initialize record list*/
    list_init(&reclist);
   
    /*printf("\n***UNSORTED RECORDS***\n");*/
    /*read input to a max of LINESIZE - 1*/
    while(fgets(buffer, LINESIZE, stdin)){
        if (sscanf(buffer, "%s", tmpbuffer) == 1){
            if(parse_record(buffer, &rec)){
                list_insert(&reclist, &rec);
            }
        } else 
            printf("tmp buffer is NOT ok");
    }

    printf("\n***********************************\n");
    printf("  SUMMARY OF MEMBER FEES OWING\n");
    printf("***********************************\n");

    printf("\n***************BY FEE**************\n");
    sort_by_fee(&reclist);
    printf("  FEE    LAST   FIRST    ID\n");
    for (p = reclist; p != 0; p = p->next)
        print_record(&p->data);
      
    printf("\n************BY LAST NAME***********\n");
    sort_by_lname(&reclist);
    printf("  FEE    LAST   FIRST    ID\n");
    for (p = reclist; p != 0; p = p->next)
        print_record(&p->data);
            
    printf("\n************BY FIRST NAME***********\n");
    sort_by_fname(&reclist);
    printf("  FEE    LAST   FIRST    ID\n");
    for (p = reclist; p != 0; p = p->next)
        print_record(&p->data);
            
    printf("\n****************BY ID***************\n");
    sort_by_id(&reclist);
    printf("  FEE    LAST   FIRST    ID\n");
    for (p = reclist; p != 0; p = p->next)
        print_record(&p->data);

     /*empty and free list*/ 
    list_clear(&reclist);
    
    return 0;
}

void list_init(record_list *mlist){
    *mlist = 0;
}

void list_clear(record_list *mlist){
    node *p, *q;
    for(p=*mlist; p !=0; p=q){
        q = p-> next;
        free(p);
    }
    list_init(mlist);
}

void sort_by_fee(record_list *mlist){
    int swapped; 
    node *m; 
    node *lptr = NULL; 
  
    /* Check for empty list */
    if (mlist == NULL) 
        return; 
    do
    { 
        swapped = 0; 
        m = *mlist; 
        while (m->next != lptr) 
        { 
            if (m->data.fee < m->next->data.fee) 
            {  
                swap(m, m->next); 
                swapped = 1; 
            } 
            m = m->next; 
        } 
        lptr = m; 
    } 
    while (swapped); 
}

void sort_by_lname(record_list *mlist){
    int swapped; 
    node *m; 
    node *lptr = NULL; 
  
    /* Check for empty list */
    if (mlist == NULL) 
        return; 
    do
    { 
        swapped = 0; 
        m = *mlist; 
  
        while (m->next != lptr) 
        { 
            if ((strcmp(m->data.name.last, m->next->data.name.last)) > 0) 
            
            {  
                swap(m, m->next); 
                swapped = 1; 
            } 
            m = m->next; 
        } 
        lptr = m; 
    } 
    while (swapped); 
}

void sort_by_fname(record_list *mlist){
    int swapped; 
    node *m; 
    node *lptr = NULL; 
  
    /* Check for empty list */
    if (mlist == NULL) 
        return; 
    do
    { 
        swapped = 0; 
        m = *mlist; 
        while (m->next != lptr) 
        { 
            if ((strcmp(m->data.name.first, m->next->data.name.first)) > 0) 
            
            {  
                swap(m, m->next); 
                swapped = 1; 
            } 
            m = m->next; 
        } 
        lptr = m; 
    } 
    while (swapped); 
}

void sort_by_id(record_list *mlist){
    int swapped; 
    node *m; 
    node *lptr = NULL; 
  
    /* Check for empty list */
    if (mlist == NULL) 
        return; 
    do
    { 
        swapped = 0; 
        m = *mlist; 
        while (m->next != lptr) 
        { 
            if ((strcmp(m->data.id, m->next->data.id)) > 0) 
            
            {  
                swap(m, m->next); 
                swapped = 1; 
            } 
            m = m->next; 
        } 
        lptr = m; 
    } 
    while (swapped); 
}

void swap(node *a, node *b) 
{ 
    record temp = a->data; 
    a->data = b->data; 
    b->data = temp; 
} 

int list_insert(record_list *mlist, const record *prec){ 
    node *newnode = malloc(sizeof(node));

    if (newnode == 0)
      return 0;
  
    newnode->data = *prec;
    newnode->next = *mlist;
    *mlist = newnode;
    return 1;  
}

int parse_record(const char *s, record *prec){
    int r;

    r = sscanf(s, "%s %s %s %lf", prec->id, prec->name.first, prec->name.last, &prec->fee);
       
    if(r < MINWORDSINRECORD)
        return 0;
    if(!is_valid_id(prec->id))
        return 0;

    return 1;
}

void print_record(const record *prec) {
    record rec = *prec;
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