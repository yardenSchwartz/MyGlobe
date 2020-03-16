#include "LinkedList.h"

struct LinkedList{
    Node head;
    Node end ;
    copyFunction copyFunc;
    freeFunction freeFunc;
    equalFunction compFunc;
    printFunction printFunc;
    transformIntoNumberFunction trunsFunc;
};


struct  sNode {
    Element data;
    Node next;
};

LinkedList createLinkedList (copyFunction copyf, freeFunction freef,
        equalFunction comp,printFunction print){
    if(copyf!=NULL&&freef!=NULL&&comp!=NULL&&print!=NULL) {
        LinkedList l = (LinkedList)calloc(1, sizeof(struct LinkedList));
        if (l != NULL) {
            l->head = NULL;
            l->end = NULL;
            l->copyFunc = copyf;
            l->compFunc = comp;
            l->freeFunc = freef;
            l->printFunc=print;
            return l;
        }
        else
            return NULL;
    }
    return NULL;
}

status destroyList(LinkedList l) {
    Node temp;
    Node current;
    if(l!=NULL) {
        temp = l->head;
        if (temp != NULL) {
            while (temp->next != NULL) {
                l->freeFunc(temp->data);
                current = temp;
                temp = temp->next;
                free(current);
            }
            l->freeFunc(temp->data);
            free(temp);
        }
        free(l);
        l = NULL;
        return  success;
    }
    return failure;
}

status appendNode (LinkedList l, Element value){
    if(l!=NULL&&value!=NULL){
        Node temp =(Node)calloc(1,sizeof(struct sNode));
        if(temp==NULL){
            return failure;
        }
        Element tempelem=l->copyFunc(value);
        if(tempelem==NULL){
            free(temp);
            return failure;
        }
            temp->data = tempelem;
            temp->next = NULL;
        if(l->head!=NULL) {
            l->end->next = temp;
            l->end = temp;
            return success;
        }
        else{
            l->head=temp;
            l->end=temp;
            return success;
        }
    }
    return failure;

}

status deleteNode(LinkedList l, Element elem){

    status result=failure;
    if(l!=NULL&&elem!=NULL) {
        Node temp;
        Node father = NULL;
        temp = l->head;
        while (temp != NULL) {

            if (l->compFunc(temp->data, elem) == true) {
                result = success;
                if (father != NULL) {
                    if (temp->next == NULL) {//if remain one node -> end=head
                        father->next = NULL;
                        l->end = father;
                        l->freeFunc(temp->data);
                        free(temp);
                        temp = NULL;
                    } else {
                        father->next = temp->next;
                        l->freeFunc(temp->data);
                        free(temp);
                        temp = NULL;
                    }
                } else {
                    if (temp->next == NULL) {//if remain one node -> end=head
                        l->end = NULL;
                        l->head = NULL;
                        l->freeFunc(temp->data);
                        free(temp);
                        temp = NULL;
                    } else {
                        l->head = temp->next;
                        l->freeFunc(temp->data);
                        free(temp);
                        temp = NULL;
                    }
                }
            }

            if (temp != NULL) {
                father = temp;
                temp = father->next;
            }
        }
    }
    return result;
}

void displayList(LinkedList l){
    if(l!=NULL) {
        Node temp;
        temp = l->head;
        while (temp != NULL) {
            l->printFunc(temp->data);
            temp = temp->next;
        }
    }
}


Element searchInList(LinkedList l, Element elem) {
    Node temp = NULL;
    if (l != NULL && elem != NULL) {
        Node temp;
        temp = l->head;
        while (temp != NULL) {

            if (l->compFunc(temp->data, elem)==true) {
                return temp->data;
            }
       temp= temp->next;
        }
    }
    return  temp;
}
