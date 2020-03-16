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


#ifndef UNTITLED1_COUNTRIES_H
#define UNTITLED1_COUNTRIES_H



typedef struct City* City;
typedef  struct Area* Area;
typedef struct Country* Country;

City Build_City(int size,char* name,char* nameOfFood,int num);

void FreeCity(City cCity);

char* getNameOfCountry(Country cCountry);

char* getNameOfCity(City cCity);

int getNumOfCities_InCountry(Country cCountry);

City getCityInIndex(Country cCountry,int i);

Country Add_Country (char* Country_Name, int x1, int x2, int y1, int y2);

enum e_status Add_CityToCountry (Country cCountry, City cCity);

enum e_status Delete_CityFromCountry (Country cCountry, char* City_Name);

enum e_bool Is_Point_In_Area (int x1, int y1, Country cCountry);

void Free_Country (Country cCountry);

Country copyCountry (Country cCountry);

status Print_Country (Country cCountry);

enum e_bool SearchCity(Country cCountry, char * cityName);
/*
status printKey(Element key);

int transformKey (Element key);

bool equalElementKey (Element key1,Element key2);

Element copyECountry(Element elem);

Element copyEName (Element elem);

status FreeVal(Element val);

status FreeKey (Element val);

status printValue(Element elem);

*/

#endif //UNTITLED1_COUNTRIES_H
//
