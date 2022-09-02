#ifndef KEYBOARD
#define KEYBOARD



#include <Keypad.h>
#include "food.h"
#include "lcd.h"

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
    {'1','2','3','2'},
    {'4','5','6','5'},
    {'7','8','9','8'},
    {'A','0','B','0'}
};

byte rowPins[ROWS] = {2,3,4,6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {11,10,9,8}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


char waitUntilGetKey()
{
    while(1){
        char key=keypad.getKey();
        if(key)
        {
            delay(100);
            return key;
        }
    }
}

ITEM getItemFromChar(char c)
{
    if(c=='1') return Paratha;
    else if(c=='2') return Omelete;
    else if(c=='3') return Dal;
    else if(c=='4') return Tea;
    else if(c=='5') return Singara;
    else return Samucha;
}

char keypadChooseFood()
{
    char key;
    while(1){
        key=waitUntilGetKey();
        Serial.println("KEY PRESSED "+key);
        if(key>='1' && key<='6') 
        {
            delay(100);
            break;
        }
        else if(key=='A' || key=='B'){
            delay(100);
            break;
        }
    }
    return key;
} 


int keypadGetQuantity()
{
    char key;
    while(1)
    {
        key=waitUntilGetKey();
        Serial.println("KEY PRESSED "+key);
        Serial.flush();
        if(key>='0' && key<='9')
        {
            break;
        }
    }
    return key-'0';
}

String keypadGetPin()
{
    enterPinPrompt(); 
    char key;
    String s="";
    int size=0;
    while(1)
    {
        key=waitUntilGetKey();
        if(key>='0' && key<='9')
        {
            s+=key;
            size++;
            lcd.print("*");
        }
        else if(key=='B')
        {
            s="";
            size=0;
            enterPinPrompt();//full reset of the pin
        }
        else if(key=='A') //submit pin
        {
            if(size!=4)
            {
                invalidPinLengthPrompt();
                s="";
                size=0;
                enterPinPrompt();
            }
            else
            {
                return s;
            }
        }
        if(size>4)
        {
            invalidPinLengthPrompt();
            s="";
            size=0;
            enterPinPrompt();
        }
    }
}

char keypadConfirmOrder()
{
    lcdConfirmOrderPrompt();
    while(1)
    {
        char key=waitUntilGetKey();
        if(key=='A' || key=='B') return key;
    }
    
}

#endif