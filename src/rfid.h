#ifndef RFIDCARD
#define RFIDCARD

#include <Arduino.h>
#include <MFRC522.h>

#define SS_PIN 53  /* Slave Select Pin */
#define RST_PIN 5  /* Reset Pin */

/* Create an instance of MFRC522 */
MFRC522 mfrc522(SS_PIN, RST_PIN);
/* Create an instance of MIFARE_Key */
MFRC522::MIFARE_Key key;  

byte bufferLen = 18;
byte readBlockData[18];
MFRC522::StatusCode status;


bool checkUidMatch(unsigned char a[], unsigned char b[], byte sz)
{
  for (byte i = 0; i < sz; i++)
  {
    if(a[i]!=b[i])return false;
  }
  return true;
}

String readRFIDCard()
{
    Serial.println("HELLO");
    while ( ! mfrc522.PICC_IsNewCardPresent()){}
    Serial.println("HELLO2");
    while(! mfrc522.PICC_ReadCardSerial()){}
    Serial.println("HELLO3");
    String s="";
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
      s=s+mfrc522.uid.uidByte[i];
    }
    if(SERIALDEBUG)
    {
      Serial.print("\n ***Card Detected*** ");
      Serial.print(F("Card UID:"));
      Serial.println(s);
    }
    return s;
}



#endif