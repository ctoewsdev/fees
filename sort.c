#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "sort.h"

void sort_by_fee(member_list *mlist){
    int swapped; 
    membernode *m; 
    membernode *lptr = NULL; 
  
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
                swapnode(m, m->next); 
                swapped = 1; 
            } 
            m = m->next; 
        } 
        lptr = m; 
    } 
    while (swapped); 
}

void sort_by_lname(member_list *mlist){
    int swapped; 
    membernode *m; 
    membernode *lptr = NULL; 
  
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
                swapnode(m, m->next); 
                swapped = 1; 
            } 
            m = m->next; 
        } 
        lptr = m; 
    } 
    while (swapped); 
}

void sort_by_fname(member_list *mlist){
    int swapped; 
    membernode *m; 
    membernode *lptr = NULL; 
  
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
                swapnode(m, m->next); 
                swapped = 1; 
            } 
            m = m->next; 
        } 
        lptr = m; 
    } 
    while (swapped); 
}

void sort_by_id(member_list *mlist){
    int swapped; 
    membernode *m; 
    membernode *lptr = NULL; 
  
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
                swapnode(m, m->next); 
                swapped = 1; 
            } 
            m = m->next; 
        } 
        lptr = m; 
    } 
    while (swapped); 
}

void swapnode(membernode *a, membernode *b) 
{ 
    member temp = a->data; 
    a->data = b->data; 
    b->data = temp; 
} 
