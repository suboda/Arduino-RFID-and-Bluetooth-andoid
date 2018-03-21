//SDA(SS)      D10
//MOSI         D11
//MISO         D12
//SCK          D13
//RST          D9

#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>
int sensorPin = A0;

int sensorValue = 0;
 SoftwareSerial BTserial(0, 1); 
const int RST_PIN = 9;            
const int SS_PIN = 10;            
MFRC522 mfrc522(SS_PIN, RST_PIN); 
 
void printArray(byte *buffer, byte bufferSize) {
   for (byte i = 0; i < bufferSize; i++) {
      Serial.print(buffer[i] < 0x10 ? " 0" : " ");
      Serial.print(buffer[i], HEX);
   }
}
 
void setup()
{
  BTserial.begin(9600);
 //  Serial.begin(9600);      //Inicializa la velocidad de Serial
   SPI.begin();         //Función que inicializa SPI
   mfrc522.PCD_Init();     //Función  que inicializa RFID
}
 
void loop()
{
if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
 // Serial.println();
 // Serial.print(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
   //  Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
   //  Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
//  Serial.println();
  if (content.substring(1) == "20 52 89 7C")  {
//    Serial.println("033");
//    Serial.println();
    BTserial.print(33);
    BTserial.print(";");
   delay(1000);
  }
if (content.substring(1) == "98 DE D7 B9")  {
//    Serial.println("027");
//    Serial.println();
    BTserial.print(27);
BTserial.print(";");
   delay(1000);
  }

if (content.substring(1) == "34 F3 F5 8B")  {
//    Serial.println("019");
//    Serial.println();
    BTserial.print(19);
    BTserial.print(";");
   delay(1000);
  } 
   
//sensorValue = analogRead(sensorPin);

delay(20);

}
