//
// Created by ise on 29/11/18.
//

#include "KeyValuePair.h"
#include "LinkedList.h"
#include "HashTable.h"

struct hashTable_s{
    LinkedList* table;
    int sizeOfHash;
    copyFunction copyKey;
    freeFunction freeKey;
    printFunction printKey;
    copyFunction copyValue;
    freeFunction freeValue;
    printFunction printValue;
    equalFunction equalKey;
    transformIntoNumberFunction transformKeyIntoNumber;
};

static Element copyFunc1(Element p){
    S_Pair copyP=copyPair((S_Pair )(p)) ;
    return (Element)copyP;
}

static status freeFunc1 (Element elem){
    return destroyKeyValuePair((S_Pair)elem);
}

static bool compFunc1(Element p1, Element p2){
    return isEqualKey((S_Pair)p1,(S_Pair)p2);
}

static status printFunc1 (Element elem){
    return displayValue((S_Pair)elem);
}


hashTable createHashTable(copyFunction copyKey, freeFunction freeKey, printFunction printKey, copyFunction copyValue, freeFunction freeValue, printFunction printValue, equalFunction equalKey, transformIntoNumberFunction transformKeyIntoNumber, int hashNumber)
{


    hashTable hash = (hashTable)calloc(1, sizeof(struct hashTable_s));
    if(hash==NULL){
        return NULL;
    }
    hash->table = (LinkedList*)calloc(hashNumber, sizeof(LinkedList));
    if(hash->table==NULL){
        free(hash);
        return NULL;
    }
    int i;
    int temp=-1;

    for(i=0; i<hashNumber; i++){
        hash->table[i]=createLinkedList(copyFunc1,freeFunc1,compFunc1,printFunc1);
        if(hash->table[i]==NULL){
            temp=i;
            break;
        }

    }
    if(temp!=-1){
        for(i=0;i<temp;i++){
            destroyList(hash->table[i]);
        }
        free(hash->table);
        free(hash);
        return NULL;
    }

        hash->sizeOfHash=hashNumber;
        hash->copyKey = copyKey;
        hash->copyValue = copyValue;
        hash->equalKey = equalKey;
        hash->freeKey = freeKey;
        hash->freeValue = freeValue;
        hash->printKey = printKey;
        hash->printValue = printValue;
        hash->transformKeyIntoNumber=transformKeyIntoNumber;

    return hash;
}

status destroyHashTable(hashTable hash){
    int i;
    if(hash!=NULL) {
        for (i = 0; i < hash->sizeOfHash; i++) {
            if(destroyList(hash->table[i])==failure){
                return failure;
            }
        }
        free(hash->table);
        free(hash);
    }
    return failure;
}

status addToHashTable(hashTable hash, Element key,Element value){

    int index = (hash->transformKeyIntoNumber(key));
            index=index%(hash->sizeOfHash);
    status result = failure;
    if(hash!=NULL&&key!=NULL&&value!=NULL){
        S_Pair pair = createKeyValuePair(key,value,hash->copyValue,hash->copyKey,hash->freeKey, hash->freeValue,
                hash->printKey, hash->printValue, hash->transformKeyIntoNumber,hash->equalKey);
       if(pair!=NULL) {
           result = appendNode(hash->table[index], pair);
           destroyKeyValuePair(pair);
       }

    }

    return result;
}

Element lookupInHashTable(hashTable hash, Element key){

    if(hash!=NULL&&key!=NULL) {
        int index = (hash->transformKeyIntoNumber(key)) % hash->sizeOfHash;
        S_Pair pair = createDemoKeyPair(key, hash->copyValue, hash->copyKey, hash->freeKey, hash->freeValue,
                                         hash->printKey, hash->printValue, hash->transformKeyIntoNumber,hash->equalKey);
        S_Pair tempPair = searchInList(hash->table[index],pair);
        destroyKeyValuePair(pair);
        if(tempPair==NULL) {
            return NULL;
        }
        return getValue(tempPair);
    }
    return NULL;
}


status displayHashElements(hashTable hash){

    int i;
    if(hash!=NULL) {
        for (i = 0; i < hash->sizeOfHash; i++){
            displayList(hash->table[i]);
        }
        return success;
    }
    return failure;
}

status removeFromHashTable(hashTable hash, Element key){
   if(hash!=NULL && key!=NULL) {
       int index = (hash->transformKeyIntoNumber(key)) % hash->sizeOfHash;
       S_Pair pair = createDemoKeyPair(key, hash->copyValue, hash->copyKey, hash->freeKey, hash->freeValue,
                                       hash->printKey, hash->printValue, hash->transformKeyIntoNumber, hash->equalKey);
       S_Pair tempPair = searchInList(hash->table[index], pair);
       destroyKeyValuePair(pair);
       return (deleteNode(hash->table[index],tempPair));

   }
    return  failure;


}



