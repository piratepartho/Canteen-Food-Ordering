#ifndef LCDisplay
#define LCDisplay
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "food.h"
#include "order.h"
#include "user.h"
LiquidCrystal_I2C lcd(0x27,20,4);


void showFoodMenu()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("1.Paratha");
    lcd.setCursor(0,1);
    lcd.print("2.Omlete");
    lcd.setCursor(0,2);
    lcd.print("3.Dal");
    lcd.setCursor(10,0);
    lcd.print("4.Tea");
    lcd.setCursor(10,1);
    lcd.print("5.Singara");
    lcd.setCursor(10,2);
    lcd.print("6.Samucha");
    lcd.setCursor(0,3);
    lcd.print("Cost:"+String(totalCost));
    lcd.print(" Bal:"+balance);
}

void showQuantity()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Give Quantity (0-9)");
    lcd.setCursor(4,2);
    lcd.print("Cost:"+String(totalCost));
    lcd.setCursor(4,3);
    lcd.print("Balance:"+balance);
}

void itemAddedMsg(ITEM item)
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(foodName[item]+" ADDED");
    delay(1500);
}

void noItemChoosenPrompt()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("No item Choosen");
    delay(500);
}

void pressRFIDprompt()
{
    lcd.clear();
    lcd.setCursor(6,0);
    lcd.print("WELCOME");
    lcd.setCursor(2,1);
    lcd.print("PRESS YOUR RFID");
}

void invalidCardPrompt()
{
    lcd.clear();
    lcd.setCursor(4,1);
    lcd.print("INVALID CARD");
    delay(1500);
}

void enterPinPrompt()
{
    lcd.clear();
    lcd.setCursor(7,0);
    lcd.print("WELCOME");
    lcd.setCursor(7,1);
    lcd.print(name);
    lcd.setCursor(1,2);
    lcd.print("PLEASE ENTER PIN");
    lcd.setCursor(7,3);
}

void invalidPinLengthPrompt()
{
    lcd.clear();
    lcd.setCursor(1,1);
    lcd.print("PIN MUST BE 4 DIGIT");
    delay(1500);
}

void pinOkPrompt()
{
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("LOGGED IN");
    delay(3000);
}

void wrongPinPrompt()
{
    lcd.clear();
    lcd.setCursor(4,1);
    lcd.print("PIN WRONG");
    lcd.setCursor(4,2);
    lcd.print("GOING BACK");
    delay(1500);
}

void commError()
{
    lcd.clear();
    lcd.setCursor(3,1);
    lcd.print("COMM ERROR");
    delay(1500);
}

void lcdConfirmOrderPrompt(){
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("CONFIRM ORDER");
    lcd.setCursor(3,2);
    lcd.print("A. YES");
    lcd.setCursor(3,3);
    lcd.print("B. NO");
}

void orderConfirmPrompt()
{
    lcd.clear();
    lcd.setCursor(2,1);
    lcd.print("ORDER CONFIRMED");
    lcd.setCursor(4,2);
    lcd.print("LOGGING OUT");
    delay(1500);
}

void orderFailPrompt()
{
    lcd.clear();
    lcd.setCursor(2,1);
    lcd.print("ORDER FAILED");
    lcd.setCursor(4,2);
    lcd.print("LOGGING OUT");
    delay(1500);
}

void itemLimitPrompt()
{
    lcd.clear();
    lcd.setCursor(3,1);
    lcd.print("Max 10 Quantity");
    delay(1500);
}

void balanceCrossPrompt()
{
    lcd.clear();
    lcd.setCursor(1,1);
    lcd.print("Balance Limit Cross");
    delay(1500);
}

#endif