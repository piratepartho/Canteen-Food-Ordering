#ifndef ORDER
#define ORDER

#include "food.h"
#include "lcd.h"
#include "user.h"

int totalCost=0;
int totalQuantity[TOTAL_ITEMS];

//this function reset the whole order
void resetOrder()
{
    for(int i=0;i<TOTAL_ITEMS;i++)
    {
        totalQuantity[i]=0;
    }
    totalCost=0;
    digitalWrite(12,LOW);
    digitalWrite(13,HIGH);
}

int orderItem(ITEM item,int quantity)
{
    if(totalQuantity[item]+quantity>10)
    {
        return 0;
    }
    if(totalCost+price[item]*quantity>balance.toInt())
    {
        return 2;
    }
    totalCost+=price[item]*quantity;
    totalQuantity[item]+=quantity;
    return 1;
}

#endif