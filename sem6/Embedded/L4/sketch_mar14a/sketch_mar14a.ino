#include <LiquidCrystal_I2C.h>
#define DECODE_NEC
#include <IRremote.hpp>
#include "Wheels.h"
#include "TimerOne.h"

#define IR_RECEIVE_PIN 2
#define FEEDBACK_LED 13


Wheels w;
volatile char cmd;

byte LCDAddress = 0x27;

LiquidCrystal_I2C lcd(LCDAddress, 16, 2);
  
uint8_t arrowRight[8] =
{
    0b01000,
    0b01100,
    0b00110,
    0b11111,
    0b11111,
    0b00110,
    0b01100,
    0b01000
};

int argIn = 0;

void WHL_setup() {
  w.attach(7, 8, 5, 12, 11, 6);
  
  Serial.println("Forward: WAD");
  Serial.println("Back: ZXC");
  Serial.println("Stop: S");
}

void LCD_setup() {
  Serial.setTimeout(200);

  lcd.init();
  lcd.backlight();

  lcd.createChar(0, arrowRight);
}

void IR_setup(){
  IrReceiver.begin(IR_RECEIVE_PIN);
  Serial.print(F("Ready"));
  printActiveIRProtocols(&Serial);
  Serial.println(F("at pin "));
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WHL_setup();
  LCD_setup();
//  IR_setup();
}

void loop() {
  while(Serial.available())
  { 
    cmd = Serial.read();
    switch(cmd)
    {
      case 'w': w.forward(); break;
      case 'x': w.back(); break;
      case 'a': w.forwardLeft(); break;
      case 'd': w.forwardRight(); break;
      case 'z': w.backLeft(); break;
      case 'c': w.backRight(); break;
      case 's': w.stop(); break;
      case '1': w.setSpeedLeft(75); break;
      case '2': w.setSpeedLeft(200); break;
      case '9': w.setSpeedRight(75); break;
      case '0': w.setSpeedRight(200); break;
      case '5': w.setSpeed(100); break;
    }
  }
//  if(IrReceiver.decode()){
//        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
//            Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
//            // We have an unknown protocol here, print extended info
//            IrReceiver.printIRResultRawFormatted(&Serial, true);
//            IrReceiver.resume(); // Do it here, to preserve raw data for printing with printIRResultRawFormatted()
//        } else {
//            IrReceiver.resume(); // Early enable receiving of the next IR frame
//            IrReceiver.printIRResultShort(&Serial);
//            IrReceiver.printIRSendUsage(&Serial);
//        }
//        Serial.println();
//
//        /*
//         * Finally, check the received data and perform actions according to the received command
//         */
//        if (IrReceiver.decodedIRData.command == 0x10) {
//            // do something
//        } else if (IrReceiver.decodedIRData.command == 0x11) {
//            // do something else
//        }
}

//  uint8_t barPos = 0;
//  argIn = Serial.parseInt(SKIP_ALL);
//  if(argIn <= 0) return;
//
//  lcd.clear();
//  lcd.setCursor(barPos, 1);
//  lcd.write(0);
//
//  for(int val=0;val<=argIn; val++) {
//    lcd.setCursor(0,0);
//    lcd.print(val);
//    barPos = map(val, 0, argIn, 0, 16);
//    lcd.setCursor(barPos, 1);
//    lcd.print('=');
//    lcd.write(0);
//    delay(20);
//  }
