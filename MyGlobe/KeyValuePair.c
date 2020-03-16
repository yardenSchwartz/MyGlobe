//
// Created by ise on 29/11/18.
//

#include "KeyValuePair.h"


struct KeyValuePair{
    Element key;
    Element value;
    copyFunction copyElementValue;
    copyFunction copyElementKey;
    freeFunction freeElementValue;
    freeFunction freeElementKey;
    printFunction printElementValue;
    printFunction printElementKey;
    transformIntoNumberFunction transformKey;
    equalFunction equalElementKey;
};


S_Pair createKeyValuePair(Element tempKey, Element tempValue, copyFunction copyFuncValue, copyFunction copyFuncKey, freeFunction freeFuncKey, freeFunction freeFuncValue, printFunction printFuncKey,
        printFunction printFuncValue, transformIntoNumberFunction t_Key, equalFunction equalFuncKey){

    if(copyFuncKey!=NULL && copyFuncValue!=NULL && freeFuncKey!=NULL && freeFuncValue!=NULL && printFuncKey!=NULL &&
    printFuncValue!=NULL && t_Key!=NULL && equalFuncKey!=NULL&& tempKey!=NULL
    && tempValue!=NULL){

        S_Pair pair = (S_Pair) calloc(1, sizeof(struct KeyValuePair));

        if (pair == NULL) {
            return NULL;
        }

        pair->copyElementKey = copyFuncKey;
        pair->copyElementValue = copyFuncValue;

        pair->key = pair->copyElementKey(tempKey);

        if (pair->key == NULL) {
            free(pair);
            return NULL;
        }

        pair->value= copyFuncValue(tempValue);

        if (pair->value == NULL) {
            free(pair->key);
            free(pair);
            return NULL;
        }

        pair->freeElementKey = freeFuncKey;
        pair->freeElementValue = freeFuncValue;

        pair->printElementKey = printFuncKey;
        pair->printElementValue = printFuncValue;

        pair->transformKey = t_Key;


        pair->equalElementKey = equalFuncKey;

        return pair;
    }
    return NULL;
}

//This function similiar to createKeyPair, but the difference is that here the value of the pair is NULL
S_Pair createDemoKeyPair (Element tempKey, copyFunction copyFuncValue, copyFunction copyFuncKey, freeFunction freeFuncKey, freeFunction freeFuncValue, printFunction printFuncKey,
                          printFunction printFuncValue, transformIntoNumberFunction t_Key, equalFunction equalFuncKey){

    if(copyFuncKey!=NULL && copyFuncValue!=NULL && freeFuncKey!=NULL && freeFuncValue!=NULL && printFuncKey!=NULL &&
       printFuncValue!=NULL && t_Key!=NULL && equalFuncKey!=NULL&& tempKey!=NULL){

        S_Pair pair = (S_Pair) calloc(1, sizeof(struct KeyValuePair));

        if (pair == NULL) {
            return NULL;
        }

        pair->copyElementKey = copyFuncKey;
        pair->copyElementValue = copyFuncValue;

        pair->key = pair->copyElementKey(tempKey);

        if (pair->key == NULL) {
            free(pair);
            return NULL;
        }

        pair->value= NULL;



        pair->freeElementKey = freeFuncKey;
        pair->freeElementValue = freeFuncValue;

        pair->printElementKey = printFuncKey;
        pair->printElementValue = printFuncValue;

        pair->transformKey = t_Key;


        pair->equalElementKey = equalFuncKey;

        return pair;
    }
    return NULL;
}

/*This function get pointer to pair (include key and value) and delete this pair*/
status destroyKeyValuePair(S_Pair sPair) {
    status result=failure;
    if (sPair != NULL) {
        sPair->freeElementValue(sPair->value);
        sPair->freeElementKey(sPair->key);
        free(sPair);
        sPair = NULL;
        result=success;
    }
    return result;

}

/*This function get pointer to pair and print the value*/
status displayValue(S_Pair sPair) {
    if (sPair != NULL) {
        sPair->printElementValue(sPair->value);
        return success;
    }
    return failure;
}

/*This function get pointer to pair and print the key*/
void displayKey(S_Pair sPair) {
    if (sPair != NULL) {
        sPair->printElementKey(sPair->key);
    }
}

void* getKey(S_Pair sPair){

    if(sPair!=NULL) {
        return sPair->key;
    }
    else
        return NULL;
}

void* getValue(S_Pair sPair){

    if(sPair!=NULL) {
        return sPair->value;
    }
    else
        return NULL;
}

bool isEqualKey(S_Pair sPair1, S_Pair sPair2){
    if(sPair1!=NULL && sPair2!=NULL){
        if(sPair1->equalElementKey==sPair2->equalElementKey) {//check it 2 of them from the same type
            if (sPair1->equalElementKey(sPair1->key, sPair2->key) == true) {//check it 2 of them from the same value of key
                return true;
            }
                else
                    return false;
        }
        else
            return false;
    }
    else
        return false;
}

S_Pair copyPair(S_Pair temp){

    Element valuep=temp->copyElementValue(temp->value);
    if(valuep==NULL){
        return NULL;
    }
    Element keyp=temp->copyElementKey(temp->key);
if(keyp==NULL){
    temp->freeElementValue(valuep);
   // free(valuep);
    return NULL;
}

    S_Pair p=createKeyValuePair(keyp,valuep,temp->copyElementValue,temp->copyElementKey,temp->freeElementKey,temp->freeElementValue,temp->printElementKey,temp->printElementValue,temp->transformKey,temp->equalElementKey);

if(p==NULL){

    temp->freeElementKey(keyp);
    //free(valuep);
    //free(keyp);
    return NULL;

}
    temp->freeElementValue(valuep);
    temp->freeElementKey(keyp);

return p;
}

