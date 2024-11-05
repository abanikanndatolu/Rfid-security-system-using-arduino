#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

// Pin definitions
#define SS_PIN 10
#define RST_PIN 9
#define GREEN_LED 6
#define RED_LED 7
#define BUZZER 8

// Initialize LCD with I2C address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 rfid(SS_PIN, RST_PIN);

// Correct RFID Card UID (Replace with your card's UID)
byte correctUID[] = {0xDE, 0xAD, 0xBE, 0xEF}; // Example UID

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  
  // Initialize RFID module
  SPI.begin();
  rfid.PCD_Init();
  
  // Initialize LCD
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to");
  lcd.setCursor(0, 1);
  lcd.print("Home Defense By Tolulope");

  delay(2000);
  lcd.clear();
  
  // Set up pins
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  // Default system status
  lcd.setCursor(0, 0);
  lcd.print("Door Status:");
  lcd.setCursor(0, 1);
  lcd.print("Locked");
  digitalWrite(RED_LED, HIGH);  // Locked (red LED on)
}

void loop() {
  // Look for new RFID cards
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Check if scanned card matches the correct UID
  if (checkUID()) {
    // Correct card
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Granted");
    unlockDoor();  // Green LED on (door unlocked)
  } else {
    // Incorrect card
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Denied");
    denyAccess();  // Sound buzzer and light red LED
  }

  delay(2000);  // Wait 2 seconds before resetting the system
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Door Status:");
  lcd.setCursor(0, 1);
  if (digitalRead(GREEN_LED) == HIGH) {
    lcd.print("Unlocked");
  } else {
    lcd.print("Locked");
  }
}

bool checkUID() {
  // Compare scanned UID with the correct UID
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] != correctUID[i]) {
      return false;  // UID does not match
    }
  }
  return true;  // UID matches
}

void unlockDoor() {
  digitalWrite(GREEN_LED, HIGH);   // Green LED on
  digitalWrite(RED_LED, LOW);      // Red LED off
}

void denyAccess() {
  digitalWrite(RED_LED, HIGH);     // Red LED on
  digitalWrite(GREEN_LED, LOW);    // Green LED off
  tone(BUZZER, 1000, 500);         // Sound buzzer
}
