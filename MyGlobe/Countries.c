//
// Created by ise on 29/11/18.
//

#include "Countries.h"

struct City{
    char* Name;
    char* NameOfFood;
    int numOfResidents;
};
struct Area{
    int x1;
    int x2;
    int y1;
    int y2;
};
struct Country{
    char* Name;
    City* cities;
    int numOfCities_InCountry;
    Area area;
};

/*This function gets parameters of city and allocate new city with all the details*/
/*return a pointer to new city*/
City Build_City(int size,char* name,char* nameOfFood,int num){
    if(name!=NULL &&nameOfFood!=NULL&&num>0,size>=0) {
     City new_City = (City) calloc(size, sizeof(struct City));
     if(new_City==NULL){
         return NULL;
     }
     new_City->Name = (char *) calloc(30, sizeof(char));
        if(new_City->Name==NULL){
            free(new_City);
            return NULL;
        }
     new_City->NameOfFood = (char *) calloc(30, sizeof(char));
        if(new_City->NameOfFood==NULL){
            free(new_City);
            free(new_City->Name);
            return NULL;
        }
     strcpy(new_City->Name, name);
     strcpy(new_City->NameOfFood, nameOfFood);
     new_City->numOfResidents = num;
     return new_City;
    }
return NULL;

}

/*This function free all fields from the exist city*/
void FreeCity(City cCity){
    if(cCity!=NULL) {
        free(cCity->Name);
        free(cCity->NameOfFood);
        free(cCity);
    }
}

/******getters******/
char* getNameOfCountry(Country cCountry){
    if(cCountry!=NULL) {
        return (cCountry->Name);
    }
    return NULL;
}

char* getNameOfCity(City cCity){
    if(cCity!=NULL) {
        return (cCity->Name);
    }
    return NULL;
}

int getNumOfCities_InCountry(Country cCountry){
    if(cCountry!=NULL) {
        return (cCountry->numOfCities_InCountry);
    }
    return-1;
}

City getCityInIndex(Country cCountry,int i){
    if(cCountry!=NULL) {
        return (cCountry->cities[i]);
    }
    return NULL;
}

static City deep_copy_city(City cCity){
    City temp_city = (City)calloc(1,(sizeof(struct City)));
    if(temp_city == NULL){
        return NULL;
    }
    else {
        temp_city->Name = (char *) calloc(strlen(cCity->Name)+1, sizeof(char));//alocated char*(length of name)
        if(temp_city->Name == NULL){
            free(temp_city);
            return NULL;
        }
        else {
            strcpy(temp_city->Name, cCity->Name);
            temp_city->NameOfFood = (char *) calloc(strlen(cCity->NameOfFood)+1, sizeof(char));//alocated char*(length of NameOfFood)
            if (temp_city->NameOfFood == NULL) {
                free(temp_city->Name);
                free(temp_city);
                return NULL;
            }
            else {
                strcpy(temp_city->NameOfFood, cCity->NameOfFood);
                temp_city->numOfResidents = cCity->numOfResidents;
            }
        }
    }
    return temp_city;
}

Country Add_Country (char* Country_Name, int x1, int x2, int y1, int y2){

    if(Country_Name!=NULL && x1>=0 && x2>=0 && y1>=0 && y2>=0){
        Country cCountry;//pointer for the country we make
        cCountry = (Country)calloc(1,(sizeof(struct Country)));
        if(cCountry==NULL){
            return NULL;
        }
        else{
            //aloocate fields of county

            cCountry->cities = (City*) malloc(sizeof(City));//at first will be empty
            *(cCountry->cities)=NULL;


            if(cCountry->cities==NULL){
                free(cCountry);
                return NULL;
            }
            cCountry->numOfCities_InCountry = 0;
            cCountry->area = (Area)calloc(1, sizeof(struct Area));

            if(cCountry->area==NULL){
                free(cCountry->cities);
                free(cCountry);
                return NULL;
            }
            else{
                cCountry->area->x1 = x1;
                cCountry->area->x2 = x2;
                cCountry->area->y1 = y1;
                cCountry->area->y2 = y2;

                cCountry->Name =(char*)calloc(1,strlen(Country_Name)+1);
                if(cCountry->Name==NULL){
                    free(cCountry->cities);
                    free(cCountry->area);
                    free(cCountry);
                    return NULL;
                }
                else{
                    strcpy(cCountry->Name,Country_Name);
                }//else name
            }//else area
        }//else cCountry
        return cCountry;
    }//if

    return NULL;
}

enum e_status Add_CityToCountry (Country cCountry, City cCity){
    if(cCountry != NULL && cCity != NULL) {
        City* tempCity = cCountry->cities;//create pointer in order to save the cities array after doing realloc
        cCountry->cities = (City*) realloc(cCountry->cities,
                                           sizeof(City) * (cCountry->numOfCities_InCountry + 1));
        if (cCountry->cities != NULL) {

            cCountry->cities[cCountry->numOfCities_InCountry] = (City) calloc(1, sizeof(struct City));//create new struct city in the end of cities array

            if (cCountry->cities[cCountry->numOfCities_InCountry] == NULL) {

                cCountry->cities = (City*) realloc(cCountry->cities,
                                                   sizeof(City) * (cCountry->numOfCities_InCountry));
                return failure;
            }
            else {
                cCountry->cities[cCountry->numOfCities_InCountry]->Name=NULL;
                cCountry->cities[cCountry->numOfCities_InCountry]->Name = (char *) calloc(strlen(cCity->Name)+1,
                                                                                          sizeof(char));
                if (cCountry->cities[cCountry->numOfCities_InCountry]->Name == NULL) {

                    free(cCountry->cities[cCountry->numOfCities_InCountry]);
                    cCountry->cities = (City*) realloc(cCountry->cities,
                                                       sizeof(City) * (cCountry->numOfCities_InCountry));//if the allocate failed, no change size of cities array

                    return failure;
                }
                else
                {
                    strcpy(cCountry->cities[cCountry->numOfCities_InCountry]->Name, cCity->Name);
                    cCountry->cities[cCountry->numOfCities_InCountry]->NameOfFood = (char *) calloc(
                            strlen(cCity->NameOfFood)+1, sizeof(char));
                    if (cCountry->cities[cCountry->numOfCities_InCountry]->NameOfFood == NULL) {

                        free(cCountry->cities[cCountry->numOfCities_InCountry]->Name);
                        free(cCountry->cities[cCountry->numOfCities_InCountry]);
                        cCountry->cities = (City*) realloc(cCountry->cities,
                                                           sizeof(City) * (cCountry->numOfCities_InCountry));//if the allocate failed, no change size of cities array

                        return failure;
                    }
                    else {
                        strcpy(cCountry->cities[cCountry->numOfCities_InCountry]->NameOfFood, cCity->NameOfFood);
                        cCountry->cities[cCountry->numOfCities_InCountry]->numOfResidents = cCity->numOfResidents;
                    }
                }
                cCountry->numOfCities_InCountry++;
                return success;
            }
        }
        else{
            cCountry->cities=tempCity;
            return failure;
        }
    }
    else
        return failure;
}

enum e_status Delete_CityFromCountry (Country cCountry, char* City_Name){

    if(cCountry == NULL || City_Name == NULL){
        return failure;
    }
    else{
        enum e_bool flag = false;
        int i;
        int tempIndex=0;//save the index of the current city
        for(i=0; i<cCountry->numOfCities_InCountry; i++){
            //this loop find the index of the current city
            if(strcmp(cCountry->cities[i]->Name, City_Name) == 0){
                flag = true;
                tempIndex=i;
                break;
            }
        }
        if(flag == false){//city not found
            return failure;
        }
        else{
            //Delete the city in temp index
            free(cCountry->cities[tempIndex]->Name);
            free(cCountry->cities[tempIndex]->NameOfFood);
            free((cCountry->cities)[tempIndex]);
            cCountry->cities[tempIndex] = NULL;

            for(int i=tempIndex; i< cCountry->numOfCities_InCountry-1; i++) {
                //this loop change each city pointer
                cCountry->cities[tempIndex] = cCountry->cities[tempIndex+1];
                tempIndex++;
            }

            cCountry->numOfCities_InCountry--;
            cCountry->cities = (City*) realloc(cCountry->cities,
                                               sizeof(City) * (cCountry->numOfCities_InCountry));

            return success;
        }
    }
}

enum e_bool Is_Point_In_Area (int x1, int y1, Country cCountry){

    int x1_Area = cCountry->area->x1;
    int x2_Area = cCountry->area->x2;
    int y1_Area = cCountry->area->y1;
    int y2_Area = cCountry->area->y2;

    if(x1_Area<=x1&&y1_Area>=y1&&x2_Area>=x1&&y2_Area<=y1){
        return true;
    }
    return false;
}

void Free_Country (Country cCountry){
    int i;
    if(cCountry!=NULL) {
        for (i = 0; i < cCountry->numOfCities_InCountry; i++) {
            free(cCountry->cities[i]->Name);
            free(cCountry->cities[i]->NameOfFood);
            free(cCountry->cities[i]);
        }
        free(cCountry->cities);

        free(cCountry->Name);
        free(cCountry->area);
        free(cCountry);
        cCountry = NULL;
    }

}

Country copyCountry (Country cCountry) {
    if(cCountry!=NULL) {
        Country new_country = (Country) calloc(1, (sizeof(struct Country)));
        if (new_country == NULL) {
            return NULL;
        } else {
            new_country->Name = (char *) calloc(strlen(cCountry->Name) + 1, sizeof(char));
            strcpy(new_country->Name, cCountry->Name);

            if (new_country->Name == NULL) {
                free(new_country);
                return NULL;
            } else {
                new_country->numOfCities_InCountry = cCountry->numOfCities_InCountry;

                new_country->area = (Area) calloc(1, sizeof(struct Area));
                if (new_country->area == NULL) {
                    free(new_country->Name);
                    free(new_country);
                    return NULL;
                } else {
                    new_country->area->x1 = cCountry->area->x1;
                    new_country->area->x2 = cCountry->area->x2;
                    new_country->area->y1 = cCountry->area->y1;
                    new_country->area->y2 = cCountry->area->y2;

                    new_country->cities = (City *) calloc(cCountry->numOfCities_InCountry, sizeof(City));
                    if (new_country->cities == NULL) {
                        free(new_country->Name);
                        free(new_country->area);
                        free(new_country);
                        return NULL;
                    } else {
                        int i;
                        enum e_bool flag = true;
                        for (i = 0; i < cCountry->numOfCities_InCountry && flag == true; i++) {
                            new_country->cities[i] = deep_copy_city(cCountry->cities[i]);
                            if (new_country->cities[i] == NULL) {
                                flag = false;
                            }
                        }
                        if (flag == false) {
                            int j;
                            for (j = 0; j < i; j++) {
                                free(new_country->cities[j]->Name);
                                free(new_country->cities[j]->NameOfFood);
                                free(new_country->cities[j]);
                            }
                            free(new_country->area);
                            free(new_country->Name);
                            free(new_country);
                            return NULL;
                        }//cities
                    }
                }//area
            }
        }//cCountry
        return new_country;
    }
    return NULL;
}
enum e_status Print_Country (Country cCountry){

    if(cCountry != NULL && cCountry->Name != NULL && cCountry->area != NULL) {
        printf("Country %s ", cCountry->Name);
        printf("coordinates: <%d,%d> , <%d,%d>\n", cCountry->area->x1, cCountry->area->y1, cCountry->area->x2,
               cCountry->area->y2);

        int m;
        if(cCountry->cities != NULL) {
            for (m = 0; m < cCountry->numOfCities_InCountry; m++) {
                printf("\t%s includes %d residents and their favorite food is %s.\n", cCountry->cities[m]->Name,
                       cCountry->cities[m]->numOfResidents, cCountry->cities[m]->NameOfFood);
            }
        }
    }
    else{
        return failure;
    }
    return success;
}

/*This function search if the current city is exist in our cities array*/
enum e_bool SearchCity(Country cCountry, char * cityName){

    enum e_bool exist=false;
    int m;
    for (m = 0; m < cCountry->numOfCities_InCountry&&exist==false; m++) {
        if(strcmp(cCountry->cities[m]->Name,cityName)==0){
            exist=true;
        }
    }
    return exist;
}


