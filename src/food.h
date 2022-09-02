#ifndef FOOD
#define FOOD

#include <Arduino.h>

#define NUMBEROFITEMS 6

enum ITEM{
    Paratha, Omelete, Dal, Tea, Singara, Samucha
};

String foodName[]={"PARTHA","OMELETE","DAL","TEA","SINGARA","SAMUCHA"};

int price[]={5,20,10,10,5,5};


ITEM currentItemChoosen;



#endif