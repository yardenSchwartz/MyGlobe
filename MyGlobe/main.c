#include <stdio.h>
#include <stddef.h>
#include "Countries.h"
#include "KeyValuePair.h"
#include "LinkedList.h"
#include "HashTable.h"



status printKey(Element key){
    printf("%s\n",(char*)key);
}

int transformKey (Element key){
    int sum=0;
    int num=0;
    int i=0;
    for(i=0;i<strlen((char*)key);i++){
        num=(int)(((char*)key)[i]);
        sum=sum+num;
    }

    return sum;
}

bool equalElementKey (Element key1,Element key2 ){

    char* one=((char*)key1);
    char* two=((char*)key2);
    if (strcmp(one,two)==0){
        return true;
    }
    return false;
}

Element copyECountry(Element elem){
    Country c=copyCountry((Country)elem);
    return (Element)(c);
}

Element copyEName (Element elem){
    char * c=(char*)calloc((strlen(((char*)elem))+1),sizeof(char));
    strcpy(c,(char*)elem);
    return c;
}

status FreeVal(Element val){
    if(val!=NULL) {
        Free_Country((Country)val);
        return success;
    }
    return failure;
}
status FreeKey (Element val){
    if(val!=NULL) {
        free((char*)val);
        return success;
    }
    return failure;
}

status printValue(Element elem){

    if(elem==NULL){
        return failure;
    }
    return  Print_Country((Country)elem);
}


int main(int argc,char* argv[]) {

    char nameOfLastCountry[12];
    FILE *Preader;
    int notMenu = 0;
    int hashSize = atoi(argv[1]);
    int CountryIndex = atoi(argv[2]);
    Preader = fopen(argv[3], "r");
    char *oneLine = (char *) calloc(300, sizeof(char));

    int numOfCountries = 0;

    //create hash to all the countries
    hashTable countriesHash = createHashTable(copyEName,FreeKey,printKey,copyECountry,FreeVal,printValue,
            equalElementKey,transformKey,hashSize);

      if (countriesHash != NULL) {

        while (fgets(oneLine, 400, Preader) != NULL && (notMenu != -1)) {//read a line
            char *name = strtok(oneLine, ",");//divide by ,
            //check if there is tab in the first word in line - city, or not - country
            //if there is tab - country
            if ((strncmp(name, "\t", 1)) != 0) {//country

                //create new country
                int x1 = atoi(strtok(NULL, ","));//casting string to int between,
                int y1 = atoi(strtok(NULL, ","));
                int x2 = atoi(strtok(NULL, ","));
                int y2 = atoi(strtok(NULL, ","));

                Country c = Add_Country(name, x1, x2, y1, y2);
                if(c!=NULL) {
                    status result = addToHashTable(countriesHash, name, c);
                    Free_Country(c);
                    if (result == failure) {
                        destroyHashTable(countriesHash);
                        notMenu = -1;
                        printf("no memory");
                    } else {
                        numOfCountries++;
                        strcpy(nameOfLastCountry, name);
                    }
                }

                else{
                    destroyHashTable(countriesHash);
                    notMenu = -1;
                    printf("no memory");
                }
            } else {//there isn't tab - city
                char *nameOfCity = (char *) calloc(30, sizeof(char));
                if (nameOfCity == NULL) {
                    destroyHashTable(countriesHash);
                    notMenu = -1;
                    printf("no memory");
                }
                else {
                    strcpy(nameOfCity, name + 1);
                    char *nameOfFood = (char *) calloc(30, sizeof(char));
                    if (nameOfFood == NULL) {
                        free(nameOfCity);
                        destroyHashTable(countriesHash);
                        notMenu = -1;
                        printf("no memory");
                    } else {
                        strcpy(nameOfFood, strtok(NULL, ","));
                        int numR = atoi(strtok(NULL, ","));

                        City newCity = Build_City(1, nameOfCity, nameOfFood, numR);
                        //send to function that build city and return pointer to city

                        if (newCity == NULL) {
                            free(nameOfCity);
                            free(nameOfFood);
                            destroyHashTable(countriesHash);
                            notMenu = -1;
                            printf("no memory");
                        } else {
                            Country currentCountry = lookupInHashTable(countriesHash, nameOfLastCountry);//return pointer to the country we search in the hass table
                            if(Add_CityToCountry(currentCountry, newCity)==failure){
                                notMenu = -1;
                                destroyHashTable(countriesHash);
                                printf("no memory");
                            }
                            free(nameOfCity);
                           free(nameOfFood);
                            FreeCity(newCity);
                        }
                    }
                }
            }
        }
    } else {
        notMenu = -1;
        printf("no memory");
    }

    fclose(Preader);
    free(oneLine);



    char *nameOfCountry;
    char newNameCountry[30];
    char cityName[30];

    City newCity;
    Country newCountry;
    status s;//status after return from function
    char *Name;
    char *NameOfFood;

    int i;
    int x1, x2;
    int y1, y2;
    char space;
    int ch = 0;
    Element e;
    status place;

    while (ch != 8 && (notMenu != -1)) {
        //if notMenu=-1 means no memory->no countries array

        printf("please choose one of the following numbers:\n");
        printf("1 : print countries\n");
        printf("2 : add country\n");
        printf("3 : add city to country\n");
        printf("4 : delete city from country\n");
        printf("5 : print country by name\n");
        printf("6 : delete country\n");
        printf("7 : is country in area\n");
        printf("8 : exit\n");
        scanf("%d", &ch);

        if (ch > 8 || (ch < 1 )) {
            printf("please choose a valid number\n");
        }

        switch (ch) {
            case 1:  /* print countries */

                displayHashElements(countriesHash);

                break;

            case 2: /* add country */
                place = failure;
                nameOfCountry = (char *) calloc(30, sizeof(char));
                if(nameOfCountry!=NULL) {
                    printf("please enter a country name\n");
                    scanf("%s", nameOfCountry);

                    if (lookupInHashTable(countriesHash, nameOfCountry) == NULL) { //country not exist
                        printf("please enter two x and y coordinates:x1,y1,x2,y2\n");
                        scanf("%d%c%d%c%d%c%d", &x1, &space, &y1, &space, &x2, &space, &y2);
                        newCountry = Add_Country(nameOfCountry, x1, x2, y1, y2);
                        if (newCountry != NULL) {
                            place = addToHashTable(countriesHash, nameOfCountry, newCountry);
                            // the inputs is valid so failure means no memory
                            if (place == failure) {
                                ch = 8;
                                printf("no memory\n");
                                free(nameOfCountry);
                                Free_Country(newCountry);
                            }
                            else {
                                free(nameOfCountry);
                                Free_Country(newCountry);
                            }
                        }
                        else{
                            free(nameOfCountry);
                            ch = 8;
                            printf("no memory\n");
                        }
                    } else {
                        printf("country with this name already exist\n");
                        free(nameOfCountry);
                    }
                }
                else{
                    ch = 8;
                    printf("no memory\n");
                }

                break;

            case 3:  /* add city to country */
                nameOfCountry = (char *) calloc(30, sizeof(char));
                Name = (char *) calloc(30, sizeof(char));
                NameOfFood = (char *) calloc(30, sizeof(char));

                if (nameOfCountry != NULL && Name != NULL && NameOfFood != NULL) {

                    printf("please enter a country name\n");
                    scanf("%s", nameOfCountry);
                    newCountry = lookupInHashTable(countriesHash, nameOfCountry);//return pointer to the country we search in the hass table
                    if (newCountry == NULL) {
                        printf("country not exist\n");
                        free(NameOfFood);
                        NameOfFood = NULL;
                        free(Name);
                        Name = NULL;

                    } else {

                        printf("please enter a city name\n");
                        scanf("%s", Name);

                        if ((SearchCity(newCountry, Name) == true)) {
                            printf("the city already exist in this country.\n");
                            free(NameOfFood);
                            NameOfFood = NULL;
                            free(Name);
                            Name = NULL;
                        } else {

                            printf("please enter the city favorite food\n");
                            scanf("%s", NameOfFood);
                            printf("please enter number of residents in city\n");
                            scanf("%d", &i);
                            newCity = Build_City(1, Name, NameOfFood, i);
                            if(newCity!=NULL) {
                                s = Add_CityToCountry(newCountry, newCity);

                                if (s == success) {
                                    printf("success\n");
                                } else {
                                    ch = 8;
                                    printf("no memory\n");
                                }
                                free(NameOfFood);
                                NameOfFood = NULL;
                                free(Name);
                                Name = NULL;
                                FreeCity(newCity);
                                newCity = NULL;
                            }
                            else{
                                free(NameOfFood);
                                NameOfFood = NULL;
                                free(Name);
                                Name = NULL;
                                ch = 8;
                                printf("no memory\n");
                            }
                        }
                    }
                    free(nameOfCountry);
                    nameOfCountry = NULL;
                } else {
                    if (nameOfCountry != NULL) {
                        free(nameOfCountry);
                    }
                    if (NameOfFood != NULL) {
                        free(NameOfFood);
                    }
                    if (Name != NULL) {
                        free(Name);
                    }
                    printf("no memory\n");
                    ch = 8;
                }
                break;

            case 4: /* delete city from country */

                printf("please enter a country name\n");
                scanf("%s", newNameCountry);

                e = lookupInHashTable(countriesHash, newNameCountry);
                if (e != NULL) {
                    printf("please enter a city name\n");
                    scanf("%s", cityName);
                    if (Delete_CityFromCountry((Country) e, cityName)==failure) {
                        printf("the city not exist in country\n");
                    }
                } else {//country not exist
                    printf("country %s not exist\n", newNameCountry);
                }

                break;

            case 5: /*print country by name*/

                printf("please enter a country name\n");
                scanf("%s", newNameCountry);

                e = lookupInHashTable(countriesHash, newNameCountry);
                if (e != NULL) {
                    Print_Country((Country) e);
                } else {
                    printf("country %s not exist\n", newNameCountry);
                }
                break;

            case 6: /*delete country*/

                printf("please enter a country name\n");
                scanf("%s", newNameCountry);

                e = lookupInHashTable(countriesHash, newNameCountry);
                if (e != NULL){
                    if(removeFromHashTable(countriesHash, newNameCountry)==success) {
                        printf("country deleted\n");
                    }
               }
               else {
                 printf("can't delete the country\n");
               }
               break;

            case 7: /*is country in area*/

                printf("please enter a country name\n");
                scanf("%s", newNameCountry);

                e = lookupInHashTable(countriesHash, newNameCountry);
                if (e != NULL){

                    printf("please enter x and y coordinations:x,y\n");
                    scanf("%d%c%d",&x1,&space,&y1);

                    if(Is_Point_In_Area(x1,y1,(Country)e)==true){
                        printf("the coordinate in the country\n");
                    }
                    else{
                        printf("the coordinate not in the country\n");
                    }
                }
                else{
                    printf("country name not exist\n");
                }

                break;
        }
    }
    if(notMenu!=-1) {//exit (case 8)
        destroyHashTable(countriesHash);
        printf("all the memory cleaned and the program is safely closed\n");
    }
    return 0;
}
