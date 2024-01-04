#include <SPI.h>
#include <Wire.h>
#include <MFRC522.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/pgmspace.h>

#define RST_PIN         9
#define SS_PIN          10
#define OLED_RESET      4
#define LED_PIN 4
#define LED_PIN1 3


MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key keyA0 = {0x0F, 0x8A, 0x8B, 0x79, 0x36, 0xD0};
MFRC522::MIFARE_Key keyA1 = {0x0F, 0x8A, 0x8B, 0x79, 0x36, 0xD0};
MFRC522::MIFARE_Key keyA2 = {0x0F, 0x8A, 0x8B, 0x79, 0x36, 0xD0};
MFRC522::MIFARE_Key keyA3 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
MFRC522::MIFARE_Key keyA4 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
MFRC522::MIFARE_Key keyA5 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
MFRC522::MIFARE_Key keyB0 = {0x31, 0xA9, 0x3D, 0x01, 0x70, 0x0F};
MFRC522::MIFARE_Key keyB1 = {0x31, 0xA9, 0x3D, 0x01, 0x70, 0x0F};
MFRC522::MIFARE_Key keyB2 = {0x31, 0xA9, 0x3D, 0x01, 0x70, 0x0F};
MFRC522::MIFARE_Key keyB3 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
MFRC522::MIFARE_Key keyB4 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
MFRC522::MIFARE_Key keyB5 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
MFRC522::StatusCode status;

                                 // Initialize the OLED display with Adafruit_SSD1306
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



void resetRC522() {              //reset lettore 
    digitalWrite(RST_PIN, LOW);  // Disattiva l'alimentazione del modulo RC522
    delay(100);                  // Attendere un breve periodo di tempo
    digitalWrite(RST_PIN, HIGH); // Riattiva l'alimentazione del modulo RC522
    delay(10);                   // Attendere un breve periodo di tempo prima di comunicare nuovamente con il modulo
}

                                 // schermo oled
void writeToOLED(const __FlashStringHelper* message) {    
  char buffer[128];
  strcpy_P(buffer, (const char*)message);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(buffer);
  display.display();
}
                                // monitor seriale
void writeToSerial(const __FlashStringHelper* message) {
  char buffer[128];
  strcpy_P(buffer, (const char*)message);
  Serial.println(buffer);
}
                                // scrittra MIFARE
void writeBytesToBlock(byte block, byte buff[], MFRC522::MIFARE_Key keyA, MFRC522::MIFARE_Key keyB) {
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &keyA, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        writeToOLED(F("ERRORE TAG   O KEY     "));
           writeToSerial(F("ERRORE TAG  O KEY   |--------|!RIAVVIO!!   "));
        digitalWrite(LED_PIN1, HIGH);                                                                     // Accende il LED portando la tensione a 5V(HIGH)
        delay(700);
        digitalWrite(LED_PIN1, LOW);                                                                      // Spegne il LED portando la tensione a 0V (LOW)
        writeToOLED(F("@SCANNING@ -------- "));
        writeToSerial(F("Ricerca nuovo tag in corso, premi un pulsante per avviare la scrittura"));
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
        display.clearDisplay();
        writeToOLED(F("SCRITTURA ESEGUITA     "));
        digitalWrite(LED_PIN, HIGH);
        writeToSerial(F("SCRITTURA ESEGUITA"));
        delay(900);
        digitalWrite(LED_PIN, LOW); // Spegne il LED portando la tensione a 0V (LOW)
        digitalWrite(LED_PIN, HIGH);
        writeToSerial(F("SCRITTURA ESEGUITA"));
        delay(900);
        digitalWrite(LED_PIN, LOW); // Spegne il LED portando la tensione a 0V (LOW)
    } else {
        writeToOLED(F("Scrittura fallita"));
        writeToSerial(F("Scrittura fallita"));
    }
}






void setup() {
    Serial.begin(9600);
    while (!Serial);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN1, OUTPUT);
   digitalWrite(LED_PIN, LOW);
   digitalWrite(LED_PIN1, LOW);
    SPI.begin();
    mfrc522.PCD_Init();

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }

    display.display();
    delay(0);
    display.clearDisplay();
    display.display();
    writeToOLED(F("@SCANNING@ -------- "));
    writeToSerial(F("Ricerca nuovo tag in corso, premi un pulsante per avviare la scrittura"));
}



 
void loop() {
   
 digitalWrite(LED_PIN, LOW);
   digitalWrite(LED_PIN1, LOW);
    
    
            // Imposta l'azione da eseguire
        digitalWrite(12, HIGH);                                                                     // Accende il LED portando la tensione a 5V(HIGH)
        delay(700);
        digitalWrite(12, LOW);                                                                      // Spegne il LED portando la tensione a 0V (LOW)
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

writeToOLED(F("RICARICA    2 EURO   -CALCOLO-"));
writeToSerial(F("RICARICA   2 EURO    -CALCOLO-"));
    writeBytesToBlock(block0, buffr0, keyA5, keyB5);
    writeBytesToBlock(block1, buffr1, keyA5, keyB5);
    writeBytesToBlock(block2, buffr2, keyA5, keyB5);
        writeToOLED(F("@SCANNING@ -------- "));
        writeToSerial(F("Ricerca nuovo tag in corso, premi un pulsante per avviare la scrittura"));
            mfrc522.PICC_HaltA();
            mfrc522.PCD_StopCrypto1();
            
      
    
                                                        
            // Aggiungi un ritardo prima di effettuare altre operazioni sul tag
            delay(500);
        
    

   
}
