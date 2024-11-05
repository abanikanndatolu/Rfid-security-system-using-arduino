Required Libraries
RFID Library: MFRC522 library
I2C LCD Library: LiquidCrystal_I2C


Components and Pin Connections
Arduino Nano
RFID Module (MFRC522): SDA -> D10, SCK -> D13, MOSI -> D11, MISO -> D12, RST -> D9
Green LED: Pin 6
Red LED: Pin 7
Buzzer: Pin 8
I2C LCD: Connect to A4 (SDA) and A5 (SCL)



To get your RFID card's UID, you can use a simple Arduino sketch to read and display the UID of your RFID card in the Serial Monitor. Here's how to do it:

Step 1: Install the MFRC522 Library
Open your Arduino IDE.
Go to Sketch > Include Library > Manage Libraries.
Search for MFRC522 and install the library by Miguel Balboa.
Step 2: use the carduid code to get your card uid
Step 3: Upload the Code to Your Arduino
Connect your Arduino Nano to your computer via USB.
Select the correct board and port from the Tools menu in the Arduino IDE.
Upload the sketch to your Arduino.
Step 4: View the RFID Card's UID
Open the Serial Monitor by going to Tools > Serial Monitor (or pressing Ctrl+Shift+M).
Set the baud rate to 9600 in the Serial Monitor.
Place your RFID card near the reader.
The UID of your card will be printed in the Serial Monitor, like this: Card UID:  0xDE 0xAD 0xBE 0xEF
Step 5: Use the UID in Your Code
Once you have the UID of your RFID card, you can use it in your main code by replacing the placeholder correctUID[] with your card's UID. For example, if your card's UID is DE AD BE EF, set it like this in your code:
byte correctUID[] = {0xDE, 0xAD, 0xBE, 0xEF};



