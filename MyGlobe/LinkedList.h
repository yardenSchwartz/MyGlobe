#include <uchar.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_


typedef struct LinkedList* LinkedList ;
typedef struct sNode* Node;


LinkedList  createLinkedList (copyFunction copyf, freeFunction freef,equalFunction comp, printFunction print);

status destroyList(LinkedList l);

status appendNode (LinkedList l, Element value);

status deleteNode(LinkedList l, Element elem);

void displayList(LinkedList l);

Element searchInList(LinkedList l, Element elem);

//status freeFunc1 (Element elem);

#endif