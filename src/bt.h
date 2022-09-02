#ifndef BTHEADER
#define BTHEADER 1

#include <Arduino.h>
#include "rfid.h"
#include "definitions.h"
#include "user.h"


HardwareSerial& hc05(Serial1);

void removeFromInputBuffer()
{
    while(hc05.available())
    {
        hc05.read();
    }
}

String getStringWithHyphenIndex(String s,int a)
{
    int cnt=0;
    String ret="";
    for(unsigned int i=0;i<s.length();i++)
    {
        if(s.charAt(i)=='-')cnt++;
        if(cnt>a) return ret;
        if(cnt==a && s.charAt(i)!='-') ret+=s.charAt(i);
    }
    if(SERIALDEBUG) Serial.println("RET "+ret);
    return ret;
}

String readFromBT()
{
    while(!hc05.available()){}
    Serial.println("RECEIVING MSG");
    String s=hc05.readStringUntil('\n');
    Serial.println("RECEIVED :"+s);
    s.trim();
    int indexOfR=s.indexOf('R');
    s=s.substring(indexOfR);
    Serial.println("RECEIVED2 :"+s);
    return s;
}

bool writeToBT(String s)
{
    removeFromInputBuffer();
    //while(!hc05.available()){}
    if(DEBUG)Serial.println("Writing MSG: ");
    if(DEBUG)Serial.println(s);
    hc05.println(s);
    hc05.flush(); //wait for the data to be sent
    if(DEBUG)Serial.println("WRITING DONE");

    //just for test now
    return 1;
}

void sendUUID(String s)
{
    s=SEND_ID_COMMAND+s;
    writeToBT(s);
}

bool verifyCard()
{
  String msg=readFromBT();
  if(getStringWithHyphenIndex(msg,0)=="R")
  {
    if(getStringWithHyphenIndex(msg,1)=="OK")
    {
        name=getStringWithHyphenIndex(msg,2);
        return 1;
    }
    else return 0;
  }
  else return 0;
}

bool checkPin(String s)
{
    //hc05.println(SEND_PASS_COMMAND+s);// \n included
    writeToBT(SEND_PASS_COMMAND+s);
    String reply=readFromBT();
    if(getStringWithHyphenIndex(reply,1)=="PASSOK")
    {
        balance=getStringWithHyphenIndex(reply,2);
        return 1;
    }
    else if(reply=="R-PASSWRONG")
    {
        return 0;
    }
    else 
    {
        if(DEBUG)
        {
            Serial.println("COMM ERROR");
            Serial.println(reply);
        }
        state=PRESS_RFID;
        return 0;
    }
}

bool sendMessage()
{
    String msg=SEND_MSG_COMMAND;
    for(int i=0;i<NUMBEROFITEMS;i++)
    {
        if(totalQuantity[i]>0)
        {
            msg+="-"+String(i)+","+String(totalQuantity[i]);
        }
    }
    writeToBT(msg);
    return 1;
}

bool  receiveMsgConfirmation()
{
    String reply=readFromBT();
    if(getStringWithHyphenIndex(reply,1)=="OK")
    {
        orderConfirmPrompt();
        return 1;
    }
    else {
        orderFailPrompt();
        return 0;
    }
}

#endif