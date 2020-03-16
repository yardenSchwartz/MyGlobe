//
// Created by ise on 29/11/18.
//
#include <uchar.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Defs.h"

#ifndef UNTITLED1_KEYVALUEPAIR_H
#define UNTITLED1_KEYVALUEPAIR_H

typedef struct KeyValuePair* S_Pair;

S_Pair createKeyValuePair(Element tempKey, Element tempValue, copyFunction copyFuncValue, copyFunction copyFuncKey,
        freeFunction freeFuncKey, freeFunction freeFuncValue, printFunction printFuncKey,printFunction printFuncValue,
        transformIntoNumberFunction t_Key, equalFunction equalFuncKey);

S_Pair createDemoKeyPair(Element tempKey, copyFunction copyFuncValue, copyFunction copyFuncKey, freeFunction freeFuncKey, freeFunction freeFuncValue, printFunction printFuncKey,
                         printFunction printFuncValue, transformIntoNumberFunction t_Key, equalFunction equalFuncKey);


status destroyKeyValuePair(S_Pair sPair);

status displayValue(S_Pair sPair);

void displayKey(S_Pair sPair);

void* getValue(S_Pair sPair);

void* getKey(S_Pair sPair);

bool isEqualKey(S_Pair sPair1, S_Pair sPair2);
S_Pair copyPair(S_Pair temp);
/*
S_Pair copyPair(S_Pair temp);

Element copyFunc1(Element p);

bool compFunc1(Element p1, Element p2);

status printFunc1 (Element elem);

status freeFunc1 (Element elem);
*/
#endif //UNTITLED1_KEYVALUEPAIR_H