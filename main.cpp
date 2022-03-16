#include <Arduino.h>
#include <SD.h>
#include <MFRC522.h>
#include <SPI.h>

// define pins for SD CARD
#define CS_SD D0
// define pins for RFID
#define CS_RFID      D8
#define RST_RFID      D4

byte nuidPICC[4];
String rfid_uid;
 
// Instance of the class for RFID
MFRC522 rfid(CS_RFID, RST_RFID);    //.....RFID_CS & RFID_RESET 
 
File myFile;

void readRFID();
void logCard();

void setup() 
{
  //pinMode(RST_RFID,OUTPUT);
  //pinMode(CS_RFID, OUTPUT);
  //pinMode(CS_SD, OUTPUT);
  delay(500);
  //digitalWrite(RST_RFID, LOW);
  SPI.begin();
  Serial.begin(9600);
  delay(1000);
  //digitalWrite(CS_RFID, LOW); 
  Serial.println("RFID initialization");
  rfid.PCD_Init();
  //delay(10);
  rfid.PCD_DumpVersionToSerial();
  Serial.println("This code scan the MIFARE Classsic NUID.");
  //delay(1000);
  //digitalWrite(CS_RFID, HIGH);
  //delay(2500);
  //digitalWrite(CS_SD, LOW);
  Serial.println("Durbin");
  delay(10); 
  if (!SD.begin(CS_SD)){
    Serial.println("Error initializing SD Card..");
  }
  myFile = SD.open("DATA.txt", FILE_WRITE);
  if (myFile) {
    Serial.println();
    Serial.println("File opened ok");
    //delay(100);
    myFile.println("THIS IS SD SETUP TEXT");  
    myFile.close();
  }
  else 
  {
    Serial.println();
    Serial.println("error opening data.txt");  
  }
  // Disables SD card chip select pin  
  //digitalWrite(CS_SD, HIGH);
  delay(1000);

}

void loop()
{
  if(rfid.PICC_IsNewCardPresent()) {
    readRFID();
    logCard();
   }
  delay(10);
}

void readRFID() 
{
  rfid_uid = "";
  if (rfid.PICC_ReadCardSerial()) 
  {
      for (int i = 0; i < 4; i++) 
      {
          nuidPICC[i] = rfid.uid.uidByte[i];
          String uid_part = String(nuidPICC[i], HEX); 
          //Serial.print(uid_part);
          rfid_uid += uid_part;
      }
      Serial.println();
  }
  Serial.print("User ID \n");
  Serial.println(rfid_uid);

  rfid.PICC_HaltA();

  //digitalWrite(CS_RFID, HIGH);
  Serial.println("RFID Deactive");
  //delay(2500);
}
 
void logCard() 
{
  //digitalWrite(CS_SD, LOW);
  Serial.println("Durbin");
  delay(10); 
//  if (!SD.begin(CS_SD)){
//    Serial.println("Error initializing SD Card..");
//  }
  myFile = SD.open("RFID.txt", FILE_WRITE);
  if (myFile) {
    Serial.println();
    Serial.println("File opened ok");
    delay(10);
    myFile.println(rfid_uid);
    myFile.println();  
    myFile.close();
  }
  else 
  {
    Serial.println();
    Serial.println("error opening data.txt");  
  }  
  //digitalWrite(CS_SD, HIGH);
  //delay(1000);
}
