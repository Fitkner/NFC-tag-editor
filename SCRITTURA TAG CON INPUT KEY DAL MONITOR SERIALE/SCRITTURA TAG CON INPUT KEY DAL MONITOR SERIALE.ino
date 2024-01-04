#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

//------------------------------------------------------------------------------------------------------------------------------------------
MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key keyA0;
MFRC522::MIFARE_Key keyB0;
MFRC522::MIFARE_Key keyA1;
MFRC522::MIFARE_Key keyB1;
MFRC522::StatusCode status;
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

void writeBytesToBlock(byte block, byte buff[], MFRC522::MIFARE_Key keyA, MFRC522::MIFARE_Key keyB) {
    
    Serial.println(F("Autenticazione con chiave B:"));
    printKey(keyB0);
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, block, &keyB, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("PCD_Authenticate(B) failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    } else {
        Serial.println(F("PCD_Authenticate(B) success: "));
    }

    Serial.println(F("Scrittura con chiave B:"));
    printKey(keyB0);
    status = mfrc522.MIFARE_Write(block, buff, 16);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Write() with key B failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    } else {
        Serial.println(F("MIFARE_Write() with key B success: "));
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------

void readKeyFromSerial(MFRC522::MIFARE_Key &key) {
    char buffer[13];
    Serial.setTimeout(5000L); 
    while (Serial.available() < sizeof(buffer) - 1) {
       
    }
    Serial.readBytesUntil('\n', buffer, sizeof(buffer)); 
    buffer[sizeof(buffer) - 1] = '\0';

    
    if (strlen(buffer) == 12) {
        for (int i = 0; i < 6; i++) {
            String byteString = String(buffer[i * 2]) + String(buffer[i * 2 + 1]);
            key.keyByte[i] = strtol(byteString.c_str(), NULL, 16);
        }
    } else {
        Serial.println(F("Errore: Lunghezza chiave non valida"));
    }
}

void printKey(MFRC522::MIFARE_Key &key) {
    Serial.print(F("Key: "));
    for (int i = 0; i < 6; i++) {
        if (key.keyByte[i] < 0x10) {
            Serial.print(F("0"));
        }
        Serial.print(key.keyByte[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
}
//------------------------------------------------------------------------------------------------------------------------------------------
void setup() {
    Serial.begin(9600);
    while (!Serial)
        ;

    Serial.println(F("keyA0 93FB38FE585A"));
    readKeyFromSerial(keyA0);
    Serial.println(F("keyB0 8380ACDC017E"));
    readKeyFromSerial(keyB0);
    Serial.println(F("keyA1 907E5C641D94"));
    readKeyFromSerial(keyA1);
    Serial.println(F("keyB1 80003D23C6F5"));
    readKeyFromSerial(keyB1);
    SPI.begin();
    mfrc522.PCD_Init();
}

//------------------------------------------------------------------------------------------------------------------------------------------
void loop() {

    if (!mfrc522.PICC_IsNewCardPresent()) {
        return;
    }

    if (!mfrc522.PICC_ReadCardSerial()) {
        return;
    }

byte block0 = 4;
    byte buffr0[] = {0x00, 0x00, 0xC6, 0xA9, 0x2F, 0x00, 0xF7, 0x09, 0xF7, 0x09, 0xB4, 0xB7, 0x00, 0x00, 0x00, 0xC1};
    byte block1 = 5;
    byte buffr1[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B};
    byte block2 = 6;
    byte buffr2[] = {0x4E, 0xA7, 0x77, 0x2F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x01, 0x00, 0x92};
    byte block3 = 8;
    byte buffr3[] = {0x10, 0xC2, 0x00, 0x00, 0xEF, 0x3D, 0xFF, 0xFF, 0x10, 0xC2, 0x00, 0x00, 0x09, 0xF6, 0x09, 0xF6};
    byte block4 = 9;
    byte buffr4[] = {0x2E, 0xC2, 0x00, 0x00, 0xD1, 0x3D, 0xFF, 0xFF, 0x2E, 0xC2, 0x00, 0x00, 0x09, 0xF6, 0x09, 0xF6};
    byte block5 = 10;
    byte buffr5[] = {0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x0A, 0xF5, 0x0A, 0xF5};
    Serial.setTimeout(5000L); 
    writeBytesToBlock(block0, buffr0, keyA0, keyB0);
    writeBytesToBlock(block1, buffr1, keyA0, keyB0);
    writeBytesToBlock(block2, buffr2, keyA0, keyB0);
    writeBytesToBlock(block3, buffr3, keyA1, keyB1);
    writeBytesToBlock(block4, buffr4, keyA1, keyB1);
    writeBytesToBlock(block5, buffr5, keyA1, keyB1);
    Serial.println(" ");
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
}
