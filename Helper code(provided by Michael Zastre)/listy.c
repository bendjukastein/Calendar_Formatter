/*
 * linkedlist.c
 *
 * Based on the implementation approach described in "The Practice 
 * of Programming" by Kernighan and Pike (Addison-Wesley, 1999).
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ics.h"
#include "emalloc.h"
#include "listy.h"


node_t *new_node(event_t *val) {
    assert( val != NULL);

    node_t *temp = (node_t *)emalloc(sizeof(node_t));

    temp->val = val;
    temp->next = NULL;

    return temp;
}


node_t *add_front(node_t *list, node_t *new) {
    new->next = list;
    return new;
}


node_t *add_end(node_t *list, node_t *new) {
    node_t *curr;

    if (list == NULL) {
        new->next = NULL;
        return new;
    }

    for (curr = list; curr->next != NULL; curr = curr->next);
    curr->next = new;
    new->next = NULL;
    return list;
}


node_t *peek_front(node_t *list) {
    return list;
}


node_t *remove_front(node_t *list) {
    if (list == NULL) {
        return NULL;
    }

    return list->next;
}



void apply(node_t *list,
           void (*fn)(node_t *list, void* arg1,void* arg2,void* arg3, void* arg4),
           void *arg1,void *arg2,void *arg3, void* arg4)
{
    for ( ; list != NULL; list = list->next) {
        (*fn)(list, arg1, arg2, arg3, arg4);
    }
}

node_t *add_inorder(node_t *list , node_t *new ){
  if(list == NULL){

   list = add_front(list, new);
   return list;
  }// if empty list
  else{
    node_t *current = list;
    if(strncmp(new->val->dtstart,current->val->dtstart,17) <0){
      return add_front(list, new);
    }//If bigger than the first object

    for ( ; current->next != NULL; current = current->next) {
        if(strncmp(new->val->dtstart,current->next->val->dtstart,17)<0){
            //if the sumary is alphabetically sooner, go one further.
            break;
      }
    }//for
    new->next = current->next;
    current->next = new;
    return list;
  }//else
}//add_inorder
