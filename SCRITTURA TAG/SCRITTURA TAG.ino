#include <SPI.h>
#include <Wire.h>
#include <MFRC522.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/pgmspace.h>

#define RST_PIN         9
#define SS_PIN          10



MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key keyA0 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
MFRC522::MIFARE_Key keyA1 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
MFRC522::MIFARE_Key keyA2 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
MFRC522::MIFARE_Key keyA3 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
MFRC522::MIFARE_Key keyA4 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
MFRC522::MIFARE_Key keyA5 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
MFRC522::MIFARE_Key keyB0 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
MFRC522::MIFARE_Key keyB1 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
MFRC522::MIFARE_Key keyB2 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
MFRC522::MIFARE_Key keyB3 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
MFRC522::MIFARE_Key keyB4 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
MFRC522::MIFARE_Key keyB5 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
MFRC522::StatusCode status;

                                



void writeToSerial(const __FlashStringHelper* message) {
  char buffer[128];
  strcpy_P(buffer, (const char*)message);
  Serial.println(buffer);
}
                                // scrittra MIFARE
void writeBytesToBlock(byte block, byte buff[], MFRC522::MIFARE_Key keyA, MFRC522::MIFARE_Key keyB) {
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &keyA, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
       
           writeToSerial(F("ERRORE TAG  O KEY   |--------|!RIAVVIO!!   "));
        writeToSerial(F("RICERCA TAG IN CORSO..."));
        writeToSerial(mfrc522.GetStatusCodeName(status));
        return;
    }
  
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, block, &keyB, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
       writeToSerial(F("AUTENTICAZIONE CON KEY B FALLITA, RIAVVIO"));
       
       writeToSerial(mfrc522.GetStatusCodeName(status));
        return;
    }

    status = mfrc522.MIFARE_Write(block, buff, 16);
    if (status == MFRC522::STATUS_OK) {
       delay(1000);
        writeToSerial(F("SCRITTURA ESEGUITA"));
        delay(900);
        writeToSerial(F("SCRITTURA ESEGUITA"));
        delay(900);
    } else {
        writeToSerial(F("SCRITTURA FALLITA"));
    }
}






void setup() {
    Serial.begin(9600);
    while (!Serial);
    SPI.begin();
    mfrc522.PCD_Init();

    writeToSerial(F("RICERCA TAG IN CORSO..."));
}



 
void loop() {
                                                                     // Spegne il LED portando la tensione a 0V (LOW)
            if (!mfrc522.PICC_IsNewCardPresent()) {
                return;
            }

            if (!mfrc522.PICC_ReadCardSerial()) {
                return;
            }

    byte block0 = 8;
    byte buffr0[] = {0x00, 0xC8, 0x00, 0xC8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x56};
    byte block1 = 9;
    byte buffr1[] = {0x00, 0x32, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55};
    byte block2 = 10;
    byte buffr2[] = {0xAA, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

writeToSerial(F("SCRITTURA"));
    writeBytesToBlock(block0, buffr0, keyA5, keyB5);
    writeBytesToBlock(block1, buffr1, keyA5, keyB5);
    writeBytesToBlock(block2, buffr2, keyA5, keyB5);
        writeToSerial(F("RICERCA TAG IN CORSO..."));
            mfrc522.PICC_HaltA();
            mfrc522.PCD_StopCrypto1();
            
      
    
                                                        
            // Aggiungi un ritardo prima di effettuare altre operazioni sul tag
            delay(500);
        
    

   
}
