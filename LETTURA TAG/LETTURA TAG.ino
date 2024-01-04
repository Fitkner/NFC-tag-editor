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
MFRC522::MIFARE_Key keyB0 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
MFRC522::MIFARE_Key keyB1 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
MFRC522::MIFARE_Key keyB2 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

#
void writeToSerial(const __FlashStringHelper* message) {
  char buffer[128];
  strcpy_P(buffer, (const char*)message);
  Serial.println(buffer);
}

void setup() {
    Serial.begin(9600);
    while (!Serial);
 
  
    SPI.begin();
    mfrc522.PCD_Init();

   

   
    writeToSerial(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
  
    if (!mfrc522.PICC_IsNewCardPresent()) {
        return;
    }

    if (!mfrc522.PICC_ReadCardSerial()) {
        return;
    }

    // Blocchi da leggere----------------------------------------------------------------------------------------------------------------------------------
    byte block0 = 8;
    byte block1 = 9;
    byte block2 = 10;

    byte buffer[18];
    byte bufferSize = sizeof(buffer);
    MFRC522::StatusCode status;
  Serial.println("Errore durante l'autenticazione con la chiave A  ");

    // Prova con la chiave B-------------------------------------------------------------------------------------------------------------------------------------
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, block1, &keyB2, &(mfrc522.uid));
    if (status == MFRC522::STATUS_OK) {
        status = mfrc522.MIFARE_Read(block1, buffer, &bufferSize);
        if (status == MFRC522::STATUS_OK) {
            Serial.println("Dati del blocco con chiave B:");
            printBlockData(buffer, bufferSize);
        } else {

            Serial.println("Errore durante la lettura del blocco con chiave B");
        }
    } else {
        Serial.println("Errore durante l'autenticazione con la chiave B  ");

       
    }
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block1, &keyA2, &(mfrc522.uid));
if (status == MFRC522::STATUS_OK) {
    status = mfrc522.MIFARE_Read(block1, buffer, &bufferSize);
    if (status == MFRC522::STATUS_OK) {
        Serial.println("Dati del blocco con chiave A:");


        printBlockData(buffer, bufferSize);
    } else {
        Serial.println("Errore durante la lettura del blocco con chiave A");

     
    }
    }

   
    // Prova con la chiave B------------------------------------------------------------------------------------------------------------------------------------
     status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, block0, &keyB2, &(mfrc522.uid));
    if (status == MFRC522::STATUS_OK) {
        status = mfrc522.MIFARE_Read(block0, buffer, &bufferSize);
        if (status == MFRC522::STATUS_OK) {
            Serial.println("Dati del blocco con chiave B:");

       
            printBlockData(buffer, bufferSize);
        } else {
            Serial.println("Errore durante la lettura del blocco con chiave B");

        
        }
    } else {
        Serial.println("Errore durante l'autenticazione con la chiave B per il blocco");
    }
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block0, &keyA2, &(mfrc522.uid));
if (status == MFRC522::STATUS_OK) {
    status = mfrc522.MIFARE_Read(block0, buffer, &bufferSize);
    if (status == MFRC522::STATUS_OK) {
        Serial.println("Dati del blocco con chiave A:");

       
        printBlockData(buffer, bufferSize);
    } else {
        Serial.println("Errore durante la lettura del blocco con chiave A");  
    }
    }
    // Prova con la chiave B-------------------------------------------------------------------------------------------------------------------------------------

     status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, block2, &keyB2, &(mfrc522.uid));
    if (status == MFRC522::STATUS_OK) {
        status = mfrc522.MIFARE_Read(block2, buffer, &bufferSize);
        if (status == MFRC522::STATUS_OK) {
            Serial.println("Dati del blocco con chiave B:");
            printBlockData(buffer, bufferSize);
        } else {
            Serial.println("Errore durante la lettura del blocco con chiave B");       
        }
    } else {
        Serial.println("Errore durante l'autenticazione con la chiave B per il blocco");

       
    }
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block2, &keyA2, &(mfrc522.uid));
if (status == MFRC522::STATUS_OK) {
    status = mfrc522.MIFARE_Read(block2, buffer, &bufferSize);
    if (status == MFRC522::STATUS_OK) {
        Serial.println("Dati del blocco con chiave A:");

                
        printBlockData(buffer, bufferSize);
    } else {
        Serial.println("Errore durante la lettura del blocco con chiave A");
    }
    }







    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    delay(1000);
    Serial.println("Scan PICC to see UID, SAK, type, and data blocks...");

}

void printBlockData(byte data[], byte length) {
    byte bytesToShow = min(16, length); // Mostra solo i primi 16 byte o meno, a seconda della lunghezza
    
    for (byte i = 0; i < bytesToShow; i++) {
        if (data[i] < 0x10) {
            Serial.print("0");  // Aggiungi uno zero se il byte è inferiore a 0x10
        }
        Serial.print(data[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
}
