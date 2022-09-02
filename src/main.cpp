#include "definitions.h"
#include <Arduino.h>
#include <SPI.h>
#include "lcd.h"
#include "rfid.h"
#include "keyborad.h"
#include "food.h"
#include "order.h"
#include "bt.h"


void setup() {
  
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  SPI.begin();
  mfrc522.PCD_Init();
  hc05.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  digitalWrite(13,HIGH);
  digitalWrite(12,LOW);
}

void loop() {
  if(state==MENU)
  {
    Serial.println("here");
    showFoodMenu();
    char key=keypadChooseFood();
    if(key=='A')
    {
      if(totalCost==0)
      {
        noItemChoosenPrompt();
      }
      else state=CONFIRM_TRANSACTION; // TODO : this will go to bill confirmation
    }
    else if(key=='B')
    {
      state=PRESS_RFID;
    }
    else if(key>='1' && key<='6')
    {
      currentItemChoosen = getItemFromChar(key);
      state=QUANTITY;
    }
  }

  else if(state==QUANTITY)
  {
    showQuantity();

    //get the quantity
    int quantity=keypadGetQuantity();
    //add the item to order array
    int val=orderItem(currentItemChoosen,quantity);
    if(val==1)
    {
      //show food add prompt
      itemAddedMsg(currentItemChoosen);
    }
    else if(val==2)
    {
      balanceCrossPrompt();
    }
    else
    {
      itemLimitPrompt();
    }
    state=MENU;
  }

  else if(state==PRESS_RFID)
  {
    resetOrder();
    pressRFIDprompt();
    String s=readRFIDCard();
    sendUUID(s); //read the card and send it via BT
    if(verifyCard())
    {
      state=ENTER_PIN;
    }
    //delay(1000);// just for test
    else
    {
      invalidCardPrompt();
    }
  }
  else if(state==ENTER_PIN)
  {
    String submittedPin=keypadGetPin();
    if(DEBUG) Serial.println(submittedPin);
    if(submittedPin=="0000")
    {
      state=PRESS_RFID;
    }
    else if(checkPin(submittedPin))
    {
      pinOkPrompt();
      digitalWrite(13,LOW);
      digitalWrite(12,HIGH);
      state=MENU;
    }
    else
    {
      wrongPinPrompt();
      state=ENTER_PIN;
    }
  }
  else if(state==CONFIRM_TRANSACTION)
  {
    char key=keypadConfirmOrder();
    if(key=='A'){
      sendMessage(); //this will send the msg
      receiveMsgConfirmation();
      state=PRESS_RFID;
    }
    else
    {
      state=MENU;
    }
  }

}